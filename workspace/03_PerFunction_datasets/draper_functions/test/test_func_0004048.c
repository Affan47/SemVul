Send(const Status & s) {
  if (GetState() != STATE_INIT && GetState() != STATE_START)
    return XMPP_RETURN_BADSTATE;

  XmlElement * presence = TranslateStatus(s);
  QueueStanza(presence);
  delete presence;
  return XMPP_RETURN_OK;
}
