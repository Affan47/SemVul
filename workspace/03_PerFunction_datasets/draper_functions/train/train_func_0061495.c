OnMessage(talk_base::Message *pmsg) {
  ASSERT(pmsg->message_id == MSG_DELETE);

  LOG_J(LS_INFO, this) << "Connection deleted";
  SignalDestroyed(this);
  delete this;
}
