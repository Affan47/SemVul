format_env_hdr(MAILSTREAM *stream, long int msgno, char *section, ENVELOPE *env,
	       fmt_env_t fmt_env, gf_io_t pc, char *field, char *oacs, int flags)
{
    register int i;

    if(!fmt_env)
      fmt_env = format_envelope;

    for(i = 0; envelope_hdrs[i].name; i++)
      if(!strucmp(field, envelope_hdrs[i].name)){
	  (*fmt_env)(stream, msgno, section, env, pc, envelope_hdrs[i].val, oacs, flags);
	  return;
      }
}
