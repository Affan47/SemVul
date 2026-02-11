on_cleared_call_cb (boost::shared_ptr<Ekiga::CallManager>  ,
                                boost::shared_ptr<Ekiga::Call> call,
                                std::string reason,
                                gpointer self)
{
  EkigaMainWindow *mw = EKIGA_MAIN_WINDOW (self);

  if (mw->priv->current_call && mw->priv->current_call->get_id () != call->get_id ()) {
    return;
  }


  if (mw->priv->current_call)
    mw->priv->current_call = boost::shared_ptr<Ekiga::Call>();
  mw->priv->calling_state = Standby;


  ekiga_main_window_flash_message (mw, "%s", reason.c_str ());


  boost::shared_ptr<Ekiga::AudioOutputCore> audiooutput_core = mw->priv->core->get<Ekiga::AudioOutputCore> ("audiooutput-core");
  audiooutput_core->stop_play_event("incoming_call_sound");
  audiooutput_core->stop_play_event("ring_tone_sound");


  g_timeout_add_seconds (2, on_delayed_hide_call_window_cb, mw);


  gtk_widget_set_sensitive (GTK_WIDGET (mw->priv->uri_toolbar), true);
  gtk_widget_set_sensitive (GTK_WIDGET (mw->priv->preview_button), true);
}
