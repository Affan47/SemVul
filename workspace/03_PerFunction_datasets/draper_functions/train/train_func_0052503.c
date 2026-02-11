check_tcl_toutlost(struct userrec *u, char *nick, char *path,
                               unsigned long acked, unsigned long length,
                               p_tcl_bind_list h)
{
  struct flag_record fr = { FR_GLOBAL | FR_CHAN | FR_ANYWH, 0, 0, 0, 0, 0 };
  char *hand = u ? u->handle : "*";
  char s[15];

  get_user_flagrec(u, &fr, NULL);
  Tcl_SetVar(interp, "_sr1", hand, 0);
  Tcl_SetVar(interp, "_sr2", nick, 0);
  Tcl_SetVar(interp, "_sr3", path, 0);
  egg_snprintf(s, sizeof s, "%lu", acked);
  Tcl_SetVar(interp, "_sr4", s, 0);
  egg_snprintf(s, sizeof s, "%lu", length);
  Tcl_SetVar(interp, "_sr5", s, 0);
  check_tcl_bind(h, hand, &fr, " $_sr1 $_sr2 $_sr3 $_sr4 $_sr5",
                 MATCH_MASK | BIND_USE_ATTR | BIND_STACKABLE);
}
