log_user_exit(struct Client *source_p)
{
  time_t on_for = CurrentTime - source_p->firsttime;
#ifdef SYSLOG_USERS
  if (IsClient(source_p))
  {
    ilog(L_INFO, "%s (%3u:%02u:%02u): %s!%s@%s %llu/%llu",
         myctime(source_p->firsttime), (unsigned int)(on_for / 3600),
         (unsigned int)((on_for % 3600)/60), (unsigned int)(on_for % 60),
         source_p->name, source_p->username, source_p->host,
         source_p->localClient->send.bytes>>10,
         source_p->localClient->recv.bytes>>10);
    }
#else
  {
    char linebuf[BUFSIZ];


    if (IsClient(source_p))
    {
      if (user_log_fb == NULL)
      {
	if ((ConfigLoggingEntry.userlog[0] != '\0') &&
	   (user_log_fb = fbopen(ConfigLoggingEntry.userlog, "r")) != NULL)
	{
	  fbclose(user_log_fb);
	  user_log_fb = fbopen(ConfigLoggingEntry.userlog, "a");
	}
      }

      if (user_log_fb != NULL)
      {
        size_t nbytes = ircsprintf(linebuf,
		   "%s (%3u:%02u:%02u): %s!%s@%s %llu/%llu\n",
		   myctime(source_p->firsttime),
		   (unsigned int)(on_for / 3600),
		   (unsigned int)((on_for % 3600)/60),
		   (unsigned int)(on_for % 60),
		   source_p->name, source_p->username, source_p->host,
		   source_p->localClient->send.bytes>>10,
		   source_p->localClient->recv.bytes>>10);
	fbputs(linebuf, user_log_fb, nbytes);
      }
    }
  }
#endif
}
