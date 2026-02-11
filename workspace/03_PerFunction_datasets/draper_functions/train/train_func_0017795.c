rli_exists_bulk(CONNECTION *c, DBH *dbh, char **arglist)

{
  int			rc;
  SENDER		*sender;
  globus_rls_obj_type_t	objtype;
  char			b[BUFLEN];
  char			val[BUFLEN];
  int			nferr;
  int			exists;

  if (loglevel > 1)
    logit(LOG_DEBUG, "rli_exists_bulk:");


  if ((rc = rrpc_readstr(c, b, BUFLEN)) != GLOBUS_RLS_SUCCESS) {
    rrpc_error(c, rc, "%s", c->errmsg);
    return;
  } else if (!b || !*b) {
    rrpc_error(c, GLOBUS_RLS_BADARG, "");
    return;
  }


  if ((objtype = atoi(b)) == globus_rls_obj_rli_lrc)
    nferr = GLOBUS_RLS_LRC_NEXIST;
  else
    nferr = GLOBUS_RLS_LFN_NEXIST;

  while (1) {


    if ((rc = rrpc_readstr(c, val, BUFLEN)) != GLOBUS_RLS_SUCCESS) {
      rrpc_error(c, rc, "%s", c->errmsg);
      return;
    }
    if (!*val)
      break;


    exists = 0;


    if (rli_bloomfilter) {
      if (loglevel > 1)
	logit(LOG_DEBUG, "rli_exists_bulk: %s %d", val, objtype);
      rls_lock_get(&senderlistlock, readlock);
      for (sender = senderlist; sender; sender = sender->nxt)
        if (objtype == globus_rls_obj_rli_lrc) {
          if (strcasecmp(val, sender->lrcurl) == 0) {
	    exists = 1;
            break;
	  }
        } else {
          if (bf_testlfn(&sender->bf, val)) {
	    exists = 1;
            break;
	  }
        }
      rls_lock_release(&senderlistlock, readlock);
    } else {
      if ((rc = db_exists(dbh->rli, val, objtype,
			  c->errmsg)) == GLOBUS_RLS_SUCCESS) {
        exists = 1;
      }
    }


    if (exists)
      str2bulkcb(c, val, "");
    else
      listresult(c, val, NULL, NULL, NULL, nferr);

  }

  if (c->numrecs == 0)
    rrpc_error(c, nferr, "", NULL);
  else
    endstrcb(c, 0);
  if (loglevel > 1)
    logit(LOG_DEBUG, "rli_exists_bulk: end");
}
