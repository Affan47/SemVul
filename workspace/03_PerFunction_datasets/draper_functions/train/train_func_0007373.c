FindSession(const std::string& sid,
                                     const std::string& remote_name) {
  SessionMap::iterator iter = session_map_.find(sid);
  if (iter == session_map_.end())
    return NULL;

  Session* session = iter->second;
  if (buzz::Jid(remote_name) != buzz::Jid(session->remote_name()))
    return NULL;

  return session;
}
