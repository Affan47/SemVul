tracker_writeback_init (TrackerMinerFiles  *miner_files,
                        TrackerConfig      *config,
                        GError            **error)
{
	GError *internal_error = NULL;

	if (tracker_config_get_enable_monitors (config)) {
		initialize_all (miner_files, &internal_error);
	}

	if (internal_error) {
		g_propagate_error (error, internal_error);
	} else {
		gminer_files = g_object_ref (miner_files);
		gconfig = g_object_ref (config);
		gsig = g_signal_connect (gconfig, "notify::enable-writeback",
		                         G_CALLBACK (enable_writeback_cb),
		                         NULL);
	}
}
