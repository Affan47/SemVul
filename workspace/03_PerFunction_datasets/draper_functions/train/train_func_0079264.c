on_missed_call_cb (boost::shared_ptr<Ekiga::CallManager>  ,
                               boost::shared_ptr<Ekiga::Call> call,
                               gpointer self)
{
  EkigaCallWindow *cw = EKIGA_CALL_WINDOW (self);

  if (cw->priv->current_call && cw->priv->current_call->get_id () != call->get_id ()) {
    return;
  }

  gtk_window_set_title (GTK_WINDOW (cw), _("Call Window"));
  ekiga_call_window_update_calling_state (cw, Standby);
  ekiga_call_window_set_status (cw, _("Standby"));
}
