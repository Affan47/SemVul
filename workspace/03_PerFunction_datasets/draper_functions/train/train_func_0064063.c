do_health_check (GtkDialog *dlg, GtkBox *vbox)
{
  GtkWidget           *l, *table, *b;
  xine_health_check_t  hc;
  xine_health_check_t *results;
  int                  check;
  hc_msg_t            *msg;

  table = gtk_table_new (1, 1, FALSE);

  add_heading (vbox, _("System configuration check"));
  add_label (vbox, _("The xine engine runs certain checks on your "
		     "system configuration. Results follow:"));


  hc.cdrom_dev = xine_config_register_string(xine,
      "media.vcd.device",
      "/dev/cdrom",
      _("device used for CD-ROM drive"),
      NULL, 0, NULL, NULL);


  const char *audio_cd = xine_config_register_string(xine,
      "media.audio_cd.device",
      "/dev/cdrom",
      _("device used for CD-ROM drive"),
      NULL, 0, NULL, NULL);

  if (!audio_cd || !*audio_cd)
    audio_cd = hc.cdrom_dev;
  if (!audio_cd || !*audio_cd)
    audio_cd = "/dev/cdrom";
  if (!hc.cdrom_dev || !*hc.cdrom_dev)
    hc.cdrom_dev = audio_cd;


  hc.dvd_dev = xine_config_register_string(xine,
      "media.dvd.device",
      "/dev/dvd",
      _("device used for DVD drive"),
      NULL, 0, NULL, NULL);

  if (!hc.dvd_dev || !*hc.dvd_dev)
    hc.dvd_dev = "/dev/dvd";

  hc_update_pref ("media.audio_cd.device", audio_cd);
  hc_update_pref ("media.vcd.device", hc.cdrom_dev);
  hc_update_pref ("media.dvd.device", hc.dvd_dev);


  for (check = 0; ; ++check)
  {
    results = xine_health_check (&hc, check);

    if (results->status == XINE_HEALTH_CHECK_NO_SUCH_CHECK)
      break;

    gtk_table_resize (GTK_TABLE (table), 3, check+1);

    l = ui_label_new_with_xalign (results->title, 0);
    gtk_table_attach (GTK_TABLE (table), l, 0, 1, check, check+1, GTK_FILL,
		      GTK_SHRINK, 2, 5);

    switch (results->status)
    {
    case XINE_HEALTH_CHECK_UNSUPPORTED:
    case XINE_HEALTH_CHECK_OK:
      l = gtk_image_new_from_stock (GTK_STOCK_YES, GTK_ICON_SIZE_BUTTON);
      break;
    case XINE_HEALTH_CHECK_FAIL:
      msg = malloc (sizeof (hc_msg_t));

      msg->msg = results->msg;
      msg->explanation = results->explanation;

      b = gtk_button_new_with_label (_("Details"));
      g_signal_connect (G_OBJECT (b), "clicked", G_CALLBACK (details_cb), msg);
      gtk_table_attach (GTK_TABLE (table), b, 2, 3, check, check+1, GTK_FILL,
			GTK_SHRINK, 2, 5);

      l = gtk_image_new_from_stock (GTK_STOCK_NO, GTK_ICON_SIZE_BUTTON);
      break;
    }

    gtk_table_attach (GTK_TABLE (table), l, 1, 2, check, check+1, GTK_FILL,
		      GTK_SHRINK, 2, 5);
  }

  gtk_box_pack_start (GTK_BOX(vbox), table, FALSE, FALSE, 5);
  return FALSE;
}
