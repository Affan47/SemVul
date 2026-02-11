cb_gimmix_key_press (GtkWidget   *widget,
		GdkEventKey *event,
		gpointer     userdata)
{
	gboolean result = FALSE;
	gint state;

	if (is_user_searching())
		return result;

	if (event->type == GDK_KEY_PRESS) {
		switch (event->keyval) {
			case GDK_b:
				cb_next_button_clicked (NULL, NULL);
				result = TRUE;
				break;
			case GDK_v:
				cb_stop_button_clicked (NULL, NULL);
				result = TRUE;
				break;
			case GDK_c:
				cb_play_button_clicked (NULL, NULL);
				result = TRUE;
				break;
			case GDK_x:
				cb_play_button_clicked (NULL, NULL);
				result = TRUE;
				break;
			case GDK_z:
				cb_prev_button_clicked (NULL, NULL);
				result = TRUE;
				break;
			case GDK_i:
				cb_info_button_press (NULL, NULL, NULL);
				result = TRUE;
				break;
			case GDK_r:
				state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(repeat_toggle_button));
				if (state == TRUE)
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(repeat_toggle_button), FALSE);
				else
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(repeat_toggle_button), TRUE);
				result = TRUE;
				break;
			case GDK_s:
				state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(shuffle_toggle_button));
				if (state == TRUE)
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(shuffle_toggle_button), FALSE);
				else
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(shuffle_toggle_button), TRUE);
				result = TRUE;
				break;
			case GDK_l:
				cb_playlist_button_press (NULL, NULL, NULL);
				break;
		}
	}
	return result;
}
