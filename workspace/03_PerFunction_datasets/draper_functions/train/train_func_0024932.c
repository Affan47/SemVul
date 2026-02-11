sess_create (Any_Type arg)
{
  Sess_Private_Data *priv;
  Sess *sess;

  if (num_sessions_generated++ >= param.wsess.num_sessions)
    return -1;

  sess = sess_new ();
  if (!sess)
    return 1;

  priv = SESS_PRIVATE_DATA (sess);

  priv->num_calls_target = param.burst_len;
  issue_calls (sess, SESS_PRIVATE_DATA (sess));
  return 0;
}
