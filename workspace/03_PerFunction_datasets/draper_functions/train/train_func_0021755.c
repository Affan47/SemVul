HandleInput(
    const char* bytes, size_t len) {
  if (state_ < STATE_OPENING || state_ > STATE_OPEN)
    return XMPP_RETURN_BADSTATE;

  EnterExit ee(this);


  stanza_parser_.Parse(bytes, len, false);

  return XMPP_RETURN_OK;
}
