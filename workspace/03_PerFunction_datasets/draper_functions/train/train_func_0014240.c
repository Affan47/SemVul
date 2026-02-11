totem_time_label_set_time (TotemTimeLabel *label, gint64 _time, gint64 length)
{
	char *label_str;

	g_return_if_fail (TOTEM_IS_TIME_LABEL (label));

	if (_time / 1000 == label->priv->time / 1000 &&
	    length / 1000 == label->priv->length / 1000)
		return;

	if (length <= 0) {
		label_str = totem_time_to_string (_time);
	} else {
		char *time_str, *length_str;

		time_str = totem_time_to_string (_time);
		length_str = totem_time_to_string (length);
		if (label->priv->seeking == FALSE) {

			label_str = g_strdup_printf (_("%s / %s"), time_str, length_str);
		} else {

			label_str = g_strdup_printf (_("Seek to %s / %s"), time_str, length_str);
		}
		g_free (time_str);
		g_free (length_str);
	}

	gtk_label_set_text (GTK_LABEL (label), label_str);
	g_free (label_str);

	label->priv->time = _time;
	label->priv->length = length;
}
