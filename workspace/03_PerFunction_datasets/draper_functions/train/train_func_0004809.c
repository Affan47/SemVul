ekiga_main_window_connect_engine_signals (EkigaMainWindow *mw)
{
  boost::signals::connection conn;

  g_return_if_fail (EKIGA_IS_MAIN_WINDOW (mw));


  boost::shared_ptr<Ekiga::CallCore> call_core = mw->priv->core->get<Ekiga::CallCore> ("call-core");
  boost::shared_ptr<Ekiga::AccountCore> account_core = mw->priv->core->get<Ekiga::AccountCore> ("account-core");


  conn = account_core->account_updated.connect (boost::bind (&on_account_updated, _1, _2, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->setup_call.connect (boost::bind (&on_setup_call_cb, _1, _2, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->ringing_call.connect (boost::bind (&on_ringing_call_cb, _1, _2, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->established_call.connect (boost::bind (&on_established_call_cb, _1, _2, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->cleared_call.connect (boost::bind (&on_cleared_call_cb, _1, _2, _3, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->missed_call.connect (boost::bind (&on_missed_call_cb, _1, _2, (gpointer) mw));
  mw->priv->connections.push_back (conn);

  conn = call_core->errors.connect (boost::bind (&on_handle_errors, _1, (gpointer) mw));
  mw->priv->connections.push_back (conn);


  boost::shared_ptr<Ekiga::ContactCore> contact_core = mw->priv->core->get<Ekiga::ContactCore> ("contact-core");
  conn = contact_core->updated.connect (boost::bind (&on_some_core_updated, mw));
  mw->priv->connections.push_back (conn);
}
