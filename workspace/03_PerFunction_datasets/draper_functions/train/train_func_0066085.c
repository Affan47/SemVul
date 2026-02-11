mailesmtp_send(mailsmtp * session,
		    const char * from,
		    int return_full,
		    const char * envid,
		    clist * addresses,
		    const char * message, size_t size)
{
  int r;
  clistiter * l;

  if (!session->esmtp)
    return mailsmtp_send(session, from, addresses, message, size);

  if ((session->esmtp & MAILSMTP_ESMTP_SIZE) != 0) {
    if (session->smtp_max_msg_size != 0) {
      if (size > session->smtp_max_msg_size) {
        return MAILSMTP_ERROR_EXCEED_STORAGE_ALLOCATION;
      }
    }
  }

  r = mailesmtp_mail_size(session, from, return_full, envid, size);
  if (r != MAILSMTP_NO_ERROR)
    return r;

  for(l = clist_begin(addresses) ; l != NULL; l = clist_next(l)) {
    struct esmtp_address * addr;

    addr = clist_content(l);

    r = mailesmtp_rcpt(session, addr->address, addr->notify, addr->orcpt);
    if (r != MAILSMTP_NO_ERROR)
      return r;
  }

  r = mailsmtp_data(session);
  if (r != MAILSMTP_NO_ERROR)
    return r;

  r = mailsmtp_data_message(session, message, size);
  if (r != MAILSMTP_NO_ERROR)
    return r;

  return MAILSMTP_NO_ERROR;
}
