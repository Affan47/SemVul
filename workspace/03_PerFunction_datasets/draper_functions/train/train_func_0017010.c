setfriendmaxsec_cb (GtkWidget *spin, GtkWidget *combobox)
{
	gdouble value;
	gint unit;

	value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spin));
	unit = gtk_combo_box_get_active (GTK_COMBO_BOX (combobox));

	switch (unit)
	{
		case 0:
			local_config.friends_maxsecs = value * 86400;
			break;
		case 1:
			local_config.friends_maxsecs = value * 3600;
			break;
		case 2:
			local_config.friends_maxsecs = value * 60;
			break;
	}

	if (mydebug > 10)
		fprintf (stderr,
			"Setting max. age for friends data to %ld seconds.\n",
			local_config.friends_maxsecs);

	return TRUE;
}
