exec_stmt_while(PLpgSQL_execstate *estate, PLpgSQL_stmt_while *stmt)
{
	for (;;)
	{
		int			rc;
		bool		value;
		bool		isnull;

		value = exec_eval_boolean(estate, stmt->cond, &isnull);
		exec_eval_cleanup(estate);

		if (isnull || !value)
			break;

		rc = exec_stmts(estate, stmt->body);

		switch (rc)
		{
			case PLPGSQL_RC_OK:
				break;

			case PLPGSQL_RC_EXIT:
				if (estate->exitlabel == NULL)
					return PLPGSQL_RC_OK;
				if (stmt->label == NULL)
					return PLPGSQL_RC_EXIT;
				if (strcmp(stmt->label, estate->exitlabel) != 0)
					return PLPGSQL_RC_EXIT;
				estate->exitlabel = NULL;
				return PLPGSQL_RC_OK;

			case PLPGSQL_RC_CONTINUE:
				if (estate->exitlabel == NULL)

					break;
				else if (stmt->label != NULL &&
						 strcmp(stmt->label, estate->exitlabel) == 0)

					estate->exitlabel = NULL;
				else

					return PLPGSQL_RC_CONTINUE;
				break;

			case PLPGSQL_RC_RETURN:
			case PLPGSQL_RC_RERAISE:
				return rc;

			default:
				elog(ERROR, "unrecognized rc: %d", rc);
		}
	}

	return PLPGSQL_RC_OK;
}
