check_tcl_pubm(char *nick, char *from, char *chname, char *msg)
{
  struct flag_record fr = { FR_GLOBAL | FR_CHAN, 0, 0, 0, 0, 0 };
  int x;
  char buf[1024], host[161];
  struct userrec *u;

  simple_sprintf(buf, "%s %s", chname, msg);
  simple_sprintf(host, "%s!%s", nick, from);
  u = get_user_by_host(host);
  get_user_flagrec(u, &fr, chname);
  Tcl_SetVar(interp, "_pubm1", nick, 0);
  Tcl_SetVar(interp, "_pubm2", from, 0);
  Tcl_SetVar(interp, "_pubm3", u ? u->handle : "*", 0);
  Tcl_SetVar(interp, "_pubm4", chname, 0);
  Tcl_SetVar(interp, "_pubm5", msg, 0);
  x = check_tcl_bind(H_pubm, buf, &fr, " $_pubm1 $_pubm2 $_pubm3 $_pubm4 $_pubm5",
                     MATCH_MASK | BIND_USE_ATTR | BIND_STACKABLE | BIND_STACKRET);


  if (x == BIND_NOMATCH)
    return 0;
  if (x == BIND_EXEC_LOG)
    return 2;

  return 1;
}
