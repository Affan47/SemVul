cal_obj_weekly_find_next_position (CalObjTime *cotime,
                                   CalObjTime *event_end,
                                   RecurData *recur_data,
                                   CalObjTime *interval_end)
{
	CalObjTime week_start;

	cal_obj_time_add_days (cotime, recur_data->recur->interval * 7);


	week_start = *cotime;
	cal_obj_time_add_days (&week_start, -recur_data->weekday_offset);

#ifdef CAL_OBJ_DEBUG
	g_print ("Next  day: %s\n", cal_obj_time_to_string (cotime));
	g_print ("Week Start: %s\n", cal_obj_time_to_string (&week_start));
#endif

	if (event_end && cal_obj_time_compare (&week_start, event_end,
					       CALOBJ_DAY) > 0)
		return TRUE;
	if (interval_end && cal_obj_time_compare (&week_start, interval_end,
						  CALOBJ_DAY) > 0) {
#ifdef CAL_OBJ_DEBUG
		g_print (
			"Interval end reached: %s\n",
			cal_obj_time_to_string (interval_end));
#endif
		return TRUE;
	}

	return FALSE;
}
