check_tcl_chjn(const char *bot, const char *nick, int chan,
                    const char type, int sock, const char *host)
{
  struct flag_record fr = { FR_GLOBAL, 0, 0, 0, 0, 0 };
  char s[11], t[2], u[11];

  t[0] = type;
  t[1] = 0;
  switch (type) {
  case '*':
    fr.global = USER_OWNER;

    break;
  case '+':
    fr.global = USER_MASTER;

    break;
  case '@':
    fr.global = USER_OP;

    break;
  case '^':
    fr.global = USER_HALFOP;

    break;
  case '%':
    fr.global = USER_BOTMAST;
  }
  egg_snprintf(s, sizeof s, "%d", chan);
  egg_snprintf(u, sizeof u, "%d", sock);
  Tcl_SetVar(interp, "_chjn1", (char *) bot, 0);
  Tcl_SetVar(interp, "_chjn2", (char *) nick, 0);
  Tcl_SetVar(interp, "_chjn3", (char *) s, 0);
  Tcl_SetVar(interp, "_chjn4", (char *) t, 0);
  Tcl_SetVar(interp, "_chjn5", (char *) u, 0);
  Tcl_SetVar(interp, "_chjn6", (char *) host, 0);
  check_tcl_bind(H_chjn, s, &fr,
                 " $_chjn1 $_chjn2 $_chjn3 $_chjn4 $_chjn5 $_chjn6",
                 MATCH_MASK | BIND_STACKABLE);
}
