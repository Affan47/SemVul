remove_foreach (GtkTreeModel *model,
                         GtkTreePath *path,
                         GtkTreeIter *iter,
                         gpointer data)
{
	gint month = 0, day = 0;
	gint req_month = check_current_schedule_date_selectedDateMon();
	gint req_day = check_current_schedule_date_selectedDateDay();
	gtk_tree_model_get(GTK_TREE_MODEL(model), iter, 2, &day, 3, &month, -1);

	if (req_month == month && req_day == day)
	{
		gtk_tree_store_remove(GTK_TREE_STORE(schedule_dates_store), iter);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
