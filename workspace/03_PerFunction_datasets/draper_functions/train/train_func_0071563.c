place_call_cb (GtkWidget * ,
               gpointer data)
{
  std::string uri;
  EkigaMainWindow *mw = NULL;

  g_return_if_fail (EKIGA_IS_MAIN_WINDOW (data));

  mw = EKIGA_MAIN_WINDOW (data);

  if (mw->priv->calling_state == Standby) {

    size_t pos;


    uri = ekiga_main_window_get_call_url (mw);
    pos = uri.find (":");
    if (pos != std::string::npos)
      if (uri.substr (++pos).empty ())
        return;

    boost::shared_ptr<Ekiga::CallCore> call_core = mw->priv->core->get<Ekiga::CallCore> ("call-core");


    pos = uri.find_first_of (' ');
    if (pos != std::string::npos)
      uri = uri.substr (0, pos);


    if (!call_core->dial (uri))
      gm_statusbar_flash_message (GM_STATUSBAR (mw->priv->statusbar), _("Could not connect to remote host"));
  }
}
