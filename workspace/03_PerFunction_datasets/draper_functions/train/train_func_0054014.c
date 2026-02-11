imapdriver_cached_logout(mailsession * session)
{
  int r;

  r = mailsession_logout(get_ancestor(session));

  check_for_uid_cache(session);

  if (r == MAIL_NO_ERROR) {
    struct imap_cached_session_state_data * imap_cached_data;

    imap_cached_data = get_cached_data(session);

    free_quoted_mb(imap_cached_data);
  }

  return r;
}
