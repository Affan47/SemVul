ECPGdeallocate_all(int lineno)
{

	while (prep_stmts != NULL)
	{
		bool		b = ECPGdeallocate(lineno, ECPG_COMPAT_PGSQL, prep_stmts->name);

		if (!b)
			return false;
	}

	return true;
}
