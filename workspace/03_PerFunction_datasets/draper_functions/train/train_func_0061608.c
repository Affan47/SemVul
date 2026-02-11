ShouldSwitch(cricket::Connection* a_conn, cricket::Connection* b_conn) {
  if (a_conn == b_conn)
    return false;

  if (!a_conn || !b_conn)
    return true;

  int prefs_cmp = CompareConnections(a_conn, b_conn);
  if (prefs_cmp < 0)
    return true;
  if (prefs_cmp > 0)
    return false;

  return b_conn->rtt() <= a_conn->rtt() + kMinImprovement;
}
