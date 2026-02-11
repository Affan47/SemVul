rebuild_time_popup (EDateEdit *dedit)
{
	EDateEditPrivate *priv;
	GtkTreeModel *model;
	GtkListStore *list_store;
	GtkTreeIter iter;
	gchar buffer[40];
	gboolean use_24_hour_format;
	struct tm tmp_tm = { 0 };
	gint hour, min;

	priv = dedit->priv;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (priv->time_combo));
	list_store = GTK_LIST_STORE (model);
	gtk_list_store_clear (list_store);


	tmp_tm.tm_year = 2000;
	tmp_tm.tm_mon = 0;
	tmp_tm.tm_mday = 1;
	tmp_tm.tm_sec  = 0;
	tmp_tm.tm_isdst = 0;

	use_24_hour_format = date_edit_use_24_hour_format (priv->use_24_hour_format);

	for (hour = priv->lower_hour; hour <= priv->upper_hour; hour++) {


		if (hour == 24)
			break;


		for (min = 0;
		     min == 0 || (min < 60 && hour != priv->upper_hour);
		     min += 30) {
			tmp_tm.tm_hour = hour;
			tmp_tm.tm_min  = min;

			e_time_format_time (
				&tmp_tm, use_24_hour_format, 0,
				buffer, sizeof (buffer));


			if (use_24_hour_format && buffer[0] == '0')
				buffer[0] = ' ';

			gtk_list_store_append (list_store, &iter);
			gtk_list_store_set (list_store, &iter, 0, buffer, -1);
		}
	}
}
