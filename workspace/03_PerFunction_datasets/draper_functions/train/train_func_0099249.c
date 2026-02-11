OnIncomingTunnel(const buzz::Jid &jid,
                                           Session *session) {
  std::string content_name;
  const TunnelContentDescription* content = NULL;
  if (!FindTunnelContent(session->remote_description(),
                         &content_name, &content)) {
    session->Reject(STR_TERMINATE_INCOMPATIBLE_PARAMETERS);
    return;
  }

  SignalIncomingTunnel(this, jid, content->description, session);
}
