_fixup_recurrence_start_dates(const GDate *sx_start_date, GList *schedule)
{
    GList *iter;
    for (iter = schedule; iter != NULL; iter = iter->next)
    {
        Recurrence *r;
        GDate start, next;

        r = (Recurrence*)iter->data;

        start = *sx_start_date;
        g_date_subtract_days(&start, 1);

        g_date_clear(&next, 1);

        recurrenceNextInstance(r, &start, &next);
        g_return_if_fail(g_date_valid(&next));

        {
            gchar date_str[128];
            gchar *sched_str;

            g_date_strftime(date_str, 127, "%x", &next);
            sched_str = recurrenceToString(r);
            g_debug("setting recurrence [%s] start date to [%s]",
                    sched_str, date_str);
            g_free(sched_str);
        }

        recurrenceSet(r,
                      recurrenceGetMultiplier(r),
                      recurrenceGetPeriodType(r),
                      &next,
                      recurrenceGetWeekendAdjust(r));
    }

    if (g_list_length(schedule) == 1
            && recurrenceGetPeriodType((Recurrence*)g_list_nth_data(schedule, 0)) == PERIOD_ONCE)
    {
        char date_buf[128];
        Recurrence *fixup = (Recurrence*)g_list_nth_data(schedule, 0);
        g_date_strftime(date_buf, 127, "%x", sx_start_date);
        recurrenceSet(fixup, 1, PERIOD_ONCE, sx_start_date, WEEKEND_ADJ_NONE);
        g_debug("fixed up period=ONCE Recurrence to date [%s]", date_buf);
    }
}
