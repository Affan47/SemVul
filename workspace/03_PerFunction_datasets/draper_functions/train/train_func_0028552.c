rli_rli_delete(CONNECTION *c, DBH *dbh, char **arglist)

{
  int	rc;
  char	buf[BUFLEN];

  if (!arglist[0]) {
    rrpc_error(c, GLOBUS_RLS_BADARG, "");
    return;
  }
  if ((rc = db_update_delete(dbh->rli, canonurl(arglist[0], buf, BUFLEN),
			     arglist[1], c->errmsg)) != GLOBUS_RLS_SUCCESS) {
    rrpc_error(c, rc, "%s", c->errmsg);
    return;
  }
  rrpc_success(c);
  update_readrli(dbh->rli, &rli_rlilistlock, &rli_rlilist);
}
