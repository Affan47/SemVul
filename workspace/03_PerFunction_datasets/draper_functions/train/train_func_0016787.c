fail_lo_xact(const char *operation, bool own_transaction)
{
	PGresult   *res;

	if (own_transaction && pset.autocommit)
	{

		res = PSQLexec("ROLLBACK", false);
		PQclear(res);
	}

	return false;
}
