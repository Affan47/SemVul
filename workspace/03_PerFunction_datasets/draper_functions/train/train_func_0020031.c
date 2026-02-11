nntpdriver_cached_unseen_number(mailsession * session,
					   const char * mb,
					   uint32_t * result)
{
  uint32_t messages;
  uint32_t recent;
  uint32_t unseen;
  int r;

  r = nntpdriver_cached_status_folder(session, mb,
      &messages, &recent, &unseen);
  if (r != MAIL_NO_ERROR)
    return r;

  * result = unseen;

  return MAIL_NO_ERROR;
}
