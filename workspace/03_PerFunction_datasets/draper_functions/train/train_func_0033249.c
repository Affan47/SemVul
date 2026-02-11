sqlite_db_secondary_close()
{
	DbField *f;
	int ret, t_ret;

	ret = 0;
	for (f = fieldlist; f->name != NULL; ++f)
		if (f->secondary != NULL && (t_ret =
		    f->secondary->close(f->secondary, 0)) != 0 && ret == 0)
			ret = t_ret;

	return (ret);
}
