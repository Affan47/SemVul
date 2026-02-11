find_hotkey_from_key_id (GtkHotkeyX11Listener	*self,
						 const gchar			*key_id)
{
	GList			*iter;
	GtkHotkeyInfo   *hotkey;

	g_return_val_if_fail (GTK_HOTKEY_IS_X11_LISTENER(self), NULL);
	g_return_val_if_fail (key_id != NULL, NULL);

	for (iter = self->priv->hotkeys; iter; iter = iter->next) {
		hotkey = GTK_HOTKEY_INFO (iter->data);

		if (g_str_equal (gtk_hotkey_info_get_key_id(hotkey), key_id))
			return hotkey;
	}

	return NULL;
}
