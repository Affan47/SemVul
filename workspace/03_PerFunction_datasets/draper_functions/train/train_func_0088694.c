gnc_date_picker_get_date (GNCDatePicker *date_picker,
                          guint *day, guint *mon, guint *year)
{
    g_return_if_fail (IS_GNC_DATE_PICKER (date_picker));
    g_return_if_fail (date_picker->calendar != NULL);

    gtk_calendar_get_date (date_picker->calendar, year, mon, day);
}
