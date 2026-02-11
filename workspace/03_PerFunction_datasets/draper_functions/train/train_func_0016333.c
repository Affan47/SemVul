key_pressed_cb (GtkWidget *widget,
                GdkEvent *event,
                gpointer user_data)
{
#if !GDK_KEY_Tab
	#define GDK_KEY_Tab GDK_Tab
#endif

	GdkKeymapKey *keys = NULL;
	gint n_keys;


	if (event->type == GDK_KEY_PRESS && event->key.keyval == GDK_KEY_Tab) {

		if (gdk_keymap_get_entries_for_keyval (gdk_keymap_get_default (), GDK_KEY_Return, &keys, &n_keys)) {

			event->key.keyval = GDK_KEY_Return;
			event->key.hardware_keycode = keys[0].keycode;
		}
		g_free (keys);
	}

	return FALSE;
}
