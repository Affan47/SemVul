uu_msg_callback (void *cb, char *msg, int level)
{
  dSP;

  ENTER; SAVETMPS; PUSHMARK (SP); EXTEND (SP, 2);

  PUSHs (sv_2mortal (newSVpv (msg, 0)));
  PUSHs (sv_2mortal (newSViv (level)));

  PUTBACK; (void) perl_call_sv ((SV *)cb, G_VOID|G_DISCARD); SPAGAIN;
  PUTBACK; FREETMPS; LEAVE;
}
