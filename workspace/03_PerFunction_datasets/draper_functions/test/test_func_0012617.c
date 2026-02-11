gnc_date_edit_set_flags (GNCDateEdit *gde, GNCDateEditFlags flags)
{
    GNCDateEditFlags old_flags;

    g_return_if_fail (gde != NULL);
    g_return_if_fail (GNC_IS_DATE_EDIT (gde));

    old_flags = gde->flags;
    gde->flags = flags;

    if ((flags & GNC_DATE_EDIT_SHOW_TIME) !=
            (old_flags & GNC_DATE_EDIT_SHOW_TIME))
    {
        if (flags & GNC_DATE_EDIT_SHOW_TIME)
        {
            gtk_widget_show (gde->cal_label);
            gtk_widget_show (gde->time_entry);
            gtk_widget_show (gde->time_combo);
        }
        else
        {
            gtk_widget_hide (gde->cal_label);
            gtk_widget_hide (gde->time_entry);
            gtk_widget_hide (gde->time_combo);
        }
    }

    if ((flags & GNC_DATE_EDIT_24_HR) != (old_flags & GNC_DATE_EDIT_24_HR))

        fill_time_combo (NULL, gde);

    if ((flags & GNC_DATE_EDIT_WEEK_STARTS_ON_MONDAY)
            != (old_flags & GNC_DATE_EDIT_WEEK_STARTS_ON_MONDAY))
    {
        if (flags & GNC_DATE_EDIT_WEEK_STARTS_ON_MONDAY)
            gtk_calendar_set_display_options
            (GTK_CALENDAR (gde->calendar),
             (GTK_CALENDAR (gde->calendar)->display_flags
              | GTK_CALENDAR_WEEK_START_MONDAY));
        else
            gtk_calendar_set_display_options
            (GTK_CALENDAR (gde->calendar),
             (GTK_CALENDAR (gde->calendar)->display_flags
              & ~GTK_CALENDAR_WEEK_START_MONDAY));
    }
}
