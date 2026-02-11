gcrd_show (GncCellRendererPopup *cell,
	   const gchar              *path,
	   gint                      x1,
	   gint                      y1,
	   gint                      x2,
	   gint                      y2)
{
	GncCellRendererDate     *date;
	gint                     year;
	gint                     month;
	gint                     day;
	gint                     index;
	const gchar             *text;

	if (parent_class->show_popup) {
		parent_class->show_popup (cell,
					  path,
					  x1, y1,
					  x2, y2);
	}

	date = GNC_CELL_RENDERER_DATE (cell);

	text = gnc_popup_entry_get_text (GNC_POPUP_ENTRY (GNC_CELL_RENDERER_POPUP (cell)->editable));

        if (!(g_strcmp0(text, "")))
        {
	    date->time = gnc_time (NULL);
            gcrd_time2dmy ( date->time, &day, &month, &year);
        }
        else
        {
            date->time = gcrd_string_dmy2time (text);
            gcrd_time2dmy ( date->time, &day, &month, &year);
        }

	gtk_calendar_clear_marks (GTK_CALENDAR (date->calendar));
	gtk_calendar_select_month (GTK_CALENDAR (date->calendar), month - 1, year);

	gtk_calendar_select_day (GTK_CALENDAR (date->calendar), day);
	gtk_calendar_mark_day (GTK_CALENDAR (date->calendar), day);

}
