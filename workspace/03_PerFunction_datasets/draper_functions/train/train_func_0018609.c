init (struct backend *be)
{
  SANE_Status status;
  SANE_Int version;

  if (!be->loaded)
    {
      status = load (be);
      if (status != SANE_STATUS_GOOD)
	return status;
    }

  DBG (3, "init: initializing backend `%s'\n", be->name);

  status = (*(op_init_t)be->op[OP_INIT]) (&version, auth_callback);
  if (status != SANE_STATUS_GOOD)
    return status;

  if (SANE_VERSION_MAJOR (version) != SANE_CURRENT_MAJOR)
    {
      DBG (1,
	   "init: backend `%s' has a wrong major version (%d instead of %d)\n",
	   be->name, SANE_VERSION_MAJOR (version), SANE_CURRENT_MAJOR);
      return SANE_STATUS_INVAL;
    }
  DBG (4, "init: backend `%s' is version %d.%d.%d\n", be->name,
       SANE_VERSION_MAJOR (version), SANE_VERSION_MINOR (version),
       SANE_VERSION_BUILD (version));

  be->inited = 1;

  return SANE_STATUS_GOOD;
}
