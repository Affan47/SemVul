xmms_diskwrite_destroy (xmms_output_t *output)
{
	xmms_config_property_t *val;
	gpointer data;

	g_return_if_fail (output);

	data = xmms_output_private_data_get (output);

	val = xmms_output_config_lookup (output, "destination_directory");
	xmms_config_property_callback_remove (val, on_dest_directory_changed, data);

	xmms_object_disconnect (XMMS_OBJECT (output),
	                        XMMS_IPC_SIGNAL_PLAYBACK_CURRENTID,
	                        on_playlist_entry_changed,
	                        data);

	g_free (data);
}
