lrc_attr_add(CONNECTION *c, DBH *dbh, char **arglist)

{
  int				rc;
  globus_rls_attr_type_t	atype;
  char				*val;

  if (!arglist[0] || !arglist[1] || !arglist[2] || !arglist[3]) {
    rrpc_error(c, GLOBUS_RLS_BADARG, "");
    return;
  }

  atype = atoi(arglist[2]);
  if (atype == globus_rls_attr_type_str && !arglist[4])
    val = "";
  else
    val = arglist[4];
  if ((rc = db_attr_add(dbh->lrc, arglist[0], atoi(arglist[1]), atype,
			arglist[3], val, c->errmsg)) != GLOBUS_RLS_SUCCESS) {
    rrpc_error(c, rc, "%s", c->errmsg);
    return;
  }
  rrpc_success(c);
}
