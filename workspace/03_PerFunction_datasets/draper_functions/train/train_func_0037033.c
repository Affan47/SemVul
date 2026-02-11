tftp_do(struct connectdata *conn, bool *done)
{
  tftp_state_data_t *state;
  CURLcode result;

  *done = FALSE;

  if(!conn->proto.tftpc) {
    result = tftp_connect(conn, done);
    if(result)
      return result;
  }

  state = (tftp_state_data_t *)conn->proto.tftpc;
  if(!state)
    return CURLE_BAD_CALLING_ORDER;

  result = tftp_perform(conn, done);


  if(!result)

    result = tftp_translate_code(state->error);

  return result;
}
