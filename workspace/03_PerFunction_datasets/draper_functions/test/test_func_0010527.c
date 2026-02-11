mailsmtp_init(mailsmtp * session)
{
  int r;

  r = mailesmtp_ehlo(session);

  if (r == MAILSMTP_NO_ERROR)
    return MAILSMTP_NO_ERROR;

  r = mailsmtp_helo(session);
  if (r == MAILSMTP_NO_ERROR)
    return MAILSMTP_NO_ERROR;

  return r;
}
