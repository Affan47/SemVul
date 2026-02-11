create_session (GstRDTManager * rdtmanager, gint id)
{
  GstRDTManagerSession *sess;

  sess = g_new0 (GstRDTManagerSession, 1);
  sess->id = id;
  sess->dec = rdtmanager;
  sess->jbuf = rdt_jitter_buffer_new ();
  sess->jbuf_lock = g_mutex_new ();
  sess->jbuf_cond = g_cond_new ();
  rdtmanager->sessions = g_slist_prepend (rdtmanager->sessions, sess);

  return sess;
}
