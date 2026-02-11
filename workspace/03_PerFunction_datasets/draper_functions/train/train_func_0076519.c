OnSessionCreate(Session *session,
                                         bool received_initiate) {
  if (received_initiate) {
    session->SignalState.connect(this, &MediaSessionClient::OnSessionState);
  }
}
