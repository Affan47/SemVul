rls_admin(CONNECTION *c, DBH *dbh, char **arglist)

{
  globus_rls_admin_cmd_t	cmd;
  RLI				*rli;

  if (loglevel > 1)
    logit(LOG_DEBUG, "rls_admin: %s", PS(arglist[0]));
  if (!arglist[0]) {
    rrpc_error(c, GLOBUS_RLS_BADARG, "");
    return;
  }
  cmd = (globus_rls_admin_cmd_t) atoi(arglist[0]);
  switch (cmd) {
    case globus_rls_admin_cmd_ping:
      rrpc_success(c);
      break;

    case globus_rls_admin_cmd_quit:
      if (!(c->perms & P_ADMIN)) {
	rrpc_error(c, GLOBUS_RLS_PERM, "%s", c->dn);
	break;
      }
      rrpc_success(c);
      quitting++;
      delayquit = 2;
      globus_mutex_lock(&commonmtx);
      globus_cond_signal(&commoncond);
      globus_mutex_unlock(&commonmtx);
      break;

    case globus_rls_admin_cmd_ssu:
      if (!(c->perms & P_ADMIN)) {
	rrpc_error(c, GLOBUS_RLS_PERM, "%s", c->dn);
	break;
      }
      rrpc_success(c);
      if (lrc_server) {
	rls_lock_get(&lrc_rlilistlock, readlock);
	for (rli = lrc_rlilist; rli; rli = rli->nxt)
	  rli->softstatestart = 0;
	rls_lock_release(&lrc_rlilistlock, readlock);
	lrc_updatenow();
      }
      if (rli_server) {
	rls_lock_get(&rli_rlilistlock, readlock);
	for (rli = rli_rlilist; rli; rli = rli->nxt)
	  rli->softstatestart = 0;
	rls_lock_release(&rli_rlilistlock, readlock);
	rli_updatenow();
      }
      globus_mutex_lock(&commonmtx);
      globus_cond_signal(&commoncond);
      globus_mutex_unlock(&commonmtx);
      break;

    default:
      rrpc_error(c, GLOBUS_RLS_BADARG, "%s", arglist[0]);
      break;
  }
}
