mailsmtp_auth(mailsmtp * session, const char * user, const char * pass)
{
  if (session->auth == MAILSMTP_AUTH_NOT_CHECKED)
    return MAILSMTP_ERROR_BAD_SEQUENCE_OF_COMMAND;

  if (session->auth & MAILSMTP_AUTH_DIGEST_MD5) {
    return mailsmtp_auth_type(session, user, pass, MAILSMTP_AUTH_DIGEST_MD5);
  } else if (session->auth & MAILSMTP_AUTH_CRAM_MD5) {
    return mailsmtp_auth_type(session, user, pass, MAILSMTP_AUTH_CRAM_MD5);
  } else if (session->auth & MAILSMTP_AUTH_PLAIN) {
    return mailsmtp_auth_type(session, user, pass, MAILSMTP_AUTH_PLAIN);
  } else if (session->auth & MAILSMTP_AUTH_LOGIN) {
    return mailsmtp_auth_type(session, user, pass, MAILSMTP_AUTH_LOGIN);
  } else {
    return MAILSMTP_ERROR_AUTH_NOT_SUPPORTED;
  }
}
