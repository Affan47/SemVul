get_message_by_uid(mailsession * session,
    const char * uid, mailmessage ** result)
{
  int r;
  struct maildir * md;
  int res;
  mailmessage * msg;
  char * msg_filename;
  struct stat stat_info;

  md = get_maildir_session(session);


  r = maildir_update(md);
  if (r != MAILDIR_NO_ERROR) {
    res = maildirdriver_maildir_error_to_mail_error(r);
    goto err;
  }

  msg_filename = maildir_message_get(md, uid);
  if (msg_filename == NULL) {
    res = MAIL_ERROR_INVAL;
    goto err;
  }

  r = stat(msg_filename, &stat_info);
  free(msg_filename);
  if (r < 0) {
    res = MAIL_ERROR_INVAL;
    goto err;
  }


  msg = mailmessage_new();
  if (msg == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto err;
  }

  r = mailmessage_init(msg, session, maildir_message_driver,
      0, stat_info.st_size);
  if (r != MAIL_NO_ERROR) {
    mailmessage_free(msg);
    res = r;
    goto err;
  }

  msg->msg_uid = strdup(uid);
  if (msg->msg_uid == NULL) {
    mailmessage_free(msg);
    res = r;
    goto err;
  }

  * result = msg;

  return MAIL_NO_ERROR;

 err:
  return res;
}
