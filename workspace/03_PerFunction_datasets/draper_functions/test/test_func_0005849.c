gtk_hotkey_x11_listener_real_unbind_hotkey (GtkHotkeyListener   *base,
												GtkHotkeyInfo		*hotkey,
												GError				**error)
{
	GtkHotkeyX11Listener	*self;
	GtkHotkeyInfo			*saved_hk;
	const gchar				*signature;

	g_return_val_if_fail (GTK_HOTKEY_IS_X11_LISTENER (base), FALSE);
	g_return_val_if_fail (GTK_HOTKEY_IS_INFO (hotkey), FALSE);

	self = GTK_HOTKEY_X11_LISTENER (base);
	signature = gtk_hotkey_info_get_signature (hotkey);
	saved_hk = find_hotkey_from_key_id (self, gtk_hotkey_info_get_key_id(hotkey));

	if (!saved_hk) {
		g_set_error (error, GTK_HOTKEY_LISTENER_ERROR,
					 GTK_HOTKEY_LISTENER_ERROR_UNBIND,
					 "Failed to unregister hotkey '%s' with signature '%s'. "
					 "No hotkey with that signature is known",
					 gtk_hotkey_info_get_key_id (hotkey),
					 signature);
		return FALSE;
	}


	tomboy_keybinder_unbind (signature, hotkey_activated_cb);


	self->priv->hotkeys = g_list_remove (self->priv->hotkeys, saved_hk);
	g_object_unref (saved_hk);


	gulong handler = g_signal_handler_find (self,
											G_SIGNAL_MATCH_DATA | G_SIGNAL_MATCH_FUNC,
											0, 0, NULL, gtk_hotkey_info_activated,
											hotkey);
	if (handler == 0) {
		g_warning ("Failed to disconnect signal handler for hotkey '%s'",
				   gtk_hotkey_info_get_key_id (hotkey));
	} else {
		g_signal_handler_disconnect (self, handler);
	}

	return TRUE;

}
