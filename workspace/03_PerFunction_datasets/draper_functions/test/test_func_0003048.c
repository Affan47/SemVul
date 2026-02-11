write_activate (NautilusDiscBurn *burn,
                GtkWindow *toplevel)
{
	BraseroTrackDataCfg	*track;
	BraseroSessionCfg	*session;

	if (nautilus_disc_burn_is_empty (toplevel))
		return;

	ensure_initialized ();

	track = brasero_track_data_cfg_new ();
	brasero_track_data_cfg_add (track, BURN_URI, NULL);

	if (burn->priv->icon)
		brasero_track_data_cfg_set_icon (BRASERO_TRACK_DATA_CFG (track),
		                                 burn->priv->icon,
		                                 NULL);

	session = brasero_session_cfg_new ();
	brasero_burn_session_add_track (BRASERO_BURN_SESSION (session),
					BRASERO_TRACK (track),
					NULL);
	g_object_unref (track);

	if (burn->priv->title)
		brasero_burn_session_set_label (BRASERO_BURN_SESSION (session),
		                                burn->priv->title);


	launch_brasero_on_window_session (session,
	                                  _("CD/DVD Creator"),
	                                  NULL,
	                                  toplevel);


	g_object_unref (session);
}
