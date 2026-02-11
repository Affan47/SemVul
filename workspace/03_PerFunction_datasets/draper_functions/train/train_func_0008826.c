s_key_press_event_cb (GtkWidget   *widget,
	                                      GdkEventKey *event,
	                                      _wd         *wd)
	{
		GtkComboBox *combo;

		if (event->keyval == GDK_KEY_Return) {
			combo = GTK_COMBO_BOX (gtk_widget_get_parent (widget));
			s_combo_apply_changes (combo, wd);
		}

		return FALSE;
	}
