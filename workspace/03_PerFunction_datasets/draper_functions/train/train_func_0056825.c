video_settings_changed_cb (GtkAdjustment * ,
			   gpointer data)
{
  EkigaCallWindow *cw = EKIGA_CALL_WINDOW (data);

  boost::shared_ptr<Ekiga::VideoInputCore> videoinput_core = cw->priv->core->get<Ekiga::VideoInputCore> ("videoinput-core");

  videoinput_core->set_whiteness ((unsigned) GTK_ADJUSTMENT (cw->priv->adj_whiteness)->value);
  videoinput_core->set_brightness ((unsigned) GTK_ADJUSTMENT (cw->priv->adj_brightness)->value);
  videoinput_core->set_colour ((unsigned) GTK_ADJUSTMENT (cw->priv->adj_colour)->value);
  videoinput_core->set_contrast ((unsigned) GTK_ADJUSTMENT (cw->priv->adj_contrast)->value);
}
