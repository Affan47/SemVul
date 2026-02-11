check_db(const char *dbname, const char *role, char *param_str)
{
	char	   *tok;

	for (tok = strtok(param_str, MULTI_VALUE_SEP);
		 tok != NULL;
		 tok = strtok(NULL, MULTI_VALUE_SEP))
	{
		if (strcmp(tok, "all\n") == 0)
			return true;
		else if (strcmp(tok, "sameuser\n") == 0)
		{
			if (strcmp(dbname, role) == 0)
				return true;
		}
		else if (strcmp(tok, "samegroup\n") == 0 ||
				 strcmp(tok, "samerole\n") == 0)
		{
			if (is_member(role, dbname))
				return true;
		}
		else if (strcmp(tok, dbname) == 0)
			return true;
	}
	return false;
}
