imap_state_login_resp(struct connectdata *conn,
                                      int imapcode,
                                      imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate;

  if(imapcode != 'O') {
    failf(data, "Access denied. %c", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else

    state(conn, IMAP_STOP);

  return result;
}
