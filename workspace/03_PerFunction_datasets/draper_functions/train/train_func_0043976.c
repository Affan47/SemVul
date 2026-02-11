OnSessionState(BaseSession* session,
                                   BaseSession::State state) {
  LOG(LS_INFO) << "TunnelSession::OnSessionState("
               << talk_base::nonnull(
                    talk_base::FindLabel(state, SESSION_STATES), "Unknown")
               << ")";
  ASSERT(session == session_);

  switch (state) {
  case Session::STATE_RECEIVEDINITIATE:
    OnInitiate();
    break;
  case Session::STATE_SENTACCEPT:
  case Session::STATE_RECEIVEDACCEPT:
    OnAccept();
    break;
  case Session::STATE_SENTTERMINATE:
  case Session::STATE_RECEIVEDTERMINATE:
    OnTerminate();
    break;
  case Session::STATE_DEINIT:

    ASSERT(false);
    break;
  default:
    break;
  }
}
