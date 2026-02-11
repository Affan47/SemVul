prepare_common(int lineno, struct connection * con, const bool questionmarks, const char *name, const char *variable)
{
	struct statement *stmt;
	struct prepared_statement *this;
	PGresult   *query;


	this = (struct prepared_statement *) ecpg_alloc(sizeof(struct prepared_statement), lineno);
	if (!this)
		return false;

	stmt = (struct statement *) ecpg_alloc(sizeof(struct statement), lineno);
	if (!stmt)
	{
		ecpg_free(this);
		return false;
	}


	stmt->lineno = lineno;
	stmt->connection = con;
	stmt->command = ecpg_strdup(variable, lineno);
	stmt->inlist = stmt->outlist = NULL;


	replace_variables(&(stmt->command), lineno);


	this->name = ecpg_strdup(name, lineno);
	this->stmt = stmt;


	query = PQprepare(stmt->connection->connection, name, stmt->command, 0, NULL);
	if (!ecpg_check_PQresult(query, stmt->lineno, stmt->connection->connection, stmt->compat))
	{
		ecpg_free(stmt->command);
		ecpg_free(this->name);
		ecpg_free(this);
		ecpg_free(stmt);
		return false;
	}

	ecpg_log("prepare_common on line %d: name %s; query: \"%s\"\n", stmt->lineno, name, stmt->command);
	PQclear(query);
	this->prepared = true;

	if (con->prep_stmts == NULL)
		this->next = NULL;
	else
		this->next = con->prep_stmts;

	con->prep_stmts = this;
	return true;
}
