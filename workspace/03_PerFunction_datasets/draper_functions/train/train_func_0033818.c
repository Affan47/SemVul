DB_MakeQuery(DB_DRIVER *driver, const char *pattern, int len, int narg, GB_VALUE *arg)
{
  char *query;

  query_narg = narg;
  query_arg = arg;
  query_driver = driver;

	if (narg == 0)
		query = GB.TempString(pattern, len);
	else
  	query = GB.SubstStringAdd(pattern, len, mq_add_param);

  if (!query || *query == 0)
  {
    GB.Error("Void query");
    return NULL;
  }
  else
    return query;
}
