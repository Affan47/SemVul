tcl_eggstr(ClientData cdata, Tcl_Interp *irp,
                        EGG_CONST char *name1,
                        EGG_CONST char *name2, int flags)
{
  char *s;
  strinfo *st = (strinfo *) cdata;

  if (flags & (TCL_TRACE_READS | TCL_TRACE_UNSETS)) {
    if ((st->str == firewall) && (firewall[0])) {
      char s1[127];

      egg_snprintf(s1, sizeof s1, "%s:%d", firewall, firewallport);
      Tcl_SetVar2(interp, name1, name2, s1, TCL_GLOBAL_ONLY);
    } else
      Tcl_SetVar2(interp, name1, name2, st->str, TCL_GLOBAL_ONLY);
    if (flags & TCL_TRACE_UNSETS) {
      Tcl_TraceVar(interp, name1, TCL_TRACE_READS | TCL_TRACE_WRITES |
                   TCL_TRACE_UNSETS, tcl_eggstr, cdata);
      if ((st->max <= 0) && (protect_readonly || (st->max == 0)))
        return "read-only variable";
    }
    return NULL;
  } else {
    if ((st->max <= 0) && (protect_readonly || (st->max == 0))) {
      Tcl_SetVar2(interp, name1, name2, st->str, TCL_GLOBAL_ONLY);
      return "read-only variable";
    }
#ifdef USE_TCL_BYTE_ARRAYS
#  undef malloc
#  undef free
    {
      Tcl_Obj *obj;
      unsigned char *bytes;
      int len;

      obj = Tcl_GetVar2Ex(interp, name1, name2, 0);
      if (!obj)
        return NULL;
      len = 0;
      bytes = Tcl_GetByteArrayFromObj(obj, &len);
      if (!bytes)
        return NULL;
      s = malloc(len + 1);
      egg_memcpy(s, bytes, len);
      s[len] = 0;
    }
#else
    s = (char *) Tcl_GetVar2(interp, name1, name2, 0);
#endif
    if (s != NULL) {
      if (strlen(s) > abs(st->max))
        s[abs(st->max)] = 0;
      if (st->str == botnetnick)
        botnet_change(s);
      else if (st->str == logfile_suffix)
        logsuffix_change(s);
      else if (st->str == firewall) {
        splitc(firewall, s, ':');
        if (!firewall[0])
          strcpy(firewall, s);
        else
          firewallport = atoi(s);
      } else
        strcpy(st->str, s);
      if ((st->flags) && (s[0])) {
        if (st->str[strlen(st->str) - 1] != '/')
          strcat(st->str, "/");
      }
#ifdef USE_TCL_BYTE_ARRAYS
      free(s);
#endif
    }
    return NULL;
  }
}
