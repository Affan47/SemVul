OnSessionClosed(DebuggerAgentSession* session) {

  if (terminate_) {
    return;
  }


  ScopedLock with(session_access_);
  ASSERT(session == session_);
  if (session == session_) {
    CloseSession();
  }
}
