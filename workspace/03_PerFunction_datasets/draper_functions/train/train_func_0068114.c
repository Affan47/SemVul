as_pg_modify_accounts(pgsql_conn_t *pg_conn, uint32_t uid,
		      slurmdb_account_cond_t *acct_cond,
		      slurmdb_account_rec_t *acct)
{
	DEF_VARS;
	List ret_list = NULL;
	int rc = SLURM_SUCCESS;
	char *object = NULL, *user_name = NULL;
	char *vals = NULL, *cond = NULL, *name_char = NULL;
	time_t now = time(NULL);

	if(!acct_cond || !acct) {
		error("as/pg: modify_accounts: we need something to change");
		return NULL;
	}
	if (check_db_connection(pg_conn) != SLURM_SUCCESS)
		return NULL;

	if(acct_cond->assoc_cond)
		concat_cond_list(acct_cond->assoc_cond->acct_list,
				 NULL, "name", &cond);
	concat_cond_list(acct_cond->description_list,
			 NULL, "description", &cond);
	concat_cond_list(acct_cond->organization_list,
			 NULL, "organization", &cond);
	if (!cond) {
		errno = SLURM_NO_CHANGE_IN_DATA;
		error("as/pg: modify_accounts: no condition given");
		return NULL;
	}

	if(acct->description)
		xstrfmtcat(vals, ", description='%s'", acct->description);
	if(acct->organization)
		xstrfmtcat(vals, ", organization='%s'", acct->organization);
	if(!vals) {
		xfree(cond);
		errno = SLURM_NO_CHANGE_IN_DATA;
		error("as/pg: modify_accounts: no new values given");
		return NULL;
	}

	query = xstrdup_printf("SELECT name FROM %s WHERE deleted=0 %s;",
			       acct_table, cond);
	xfree(cond);
	result = DEF_QUERY_RET;
	if(!result) {
		xfree(vals);
		return NULL;
	}

	rc = 0;
	ret_list = list_create(slurm_destroy_char);
	FOR_EACH_ROW {
		object = xstrdup(ROW(0));
		list_append(ret_list, object);
		if(!rc) {
			xstrfmtcat(name_char, "(name='%s'", object);
			rc = 1;
		} else  {
			xstrfmtcat(name_char, " OR name='%s'", object);
		}

	} END_EACH_ROW;
	PQclear(result);

	if(!list_count(ret_list)) {
		errno = SLURM_NO_CHANGE_IN_DATA;
		debug3("as/pg: modify_accounts: didn't effect anything");
		xfree(vals);
		return ret_list;
	}
	xstrcat(name_char, ")");

	user_name = uid_to_string((uid_t) uid);
	rc = pgsql_modify_common(pg_conn, DBD_MODIFY_ACCOUNTS, now, "",
				 user_name, acct_table, name_char, vals);
	xfree(user_name);
	xfree(name_char);
	xfree(vals);

	if (rc == SLURM_ERROR) {
		error("as/pg: couldn't modify accounts");
		list_destroy(ret_list);
		errno = SLURM_ERROR;
		ret_list = NULL;
	}
	return ret_list;
}
