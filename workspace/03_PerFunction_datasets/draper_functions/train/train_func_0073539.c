cal_obj_initialize_recur_data (RecurData *recur_data,
                               ECalRecurrence *recur,
                               CalObjTime *event_start)
{
	GList *elem;
	gint month, yearday, monthday, weekday, hour, minute, second;


	memset (recur_data, 0, sizeof (RecurData));

	recur_data->recur = recur;


	recur_data->weekday_offset = cal_obj_time_weekday_offset (
		event_start,
		recur);


	elem = recur->bymonth;
	while (elem) {
		month = GPOINTER_TO_INT (elem->data);
		recur_data->months[month] = 1;
		elem = elem->next;
	}


	elem = recur->byyearday;
	while (elem) {
		yearday = GPOINTER_TO_INT (elem->data);
		if (yearday >= 0)
			recur_data->yeardays[yearday] = 1;
		else
			recur_data->neg_yeardays[-yearday] = 1;
		elem = elem->next;
	}


	elem = recur->bymonthday;
	while (elem) {
		monthday = GPOINTER_TO_INT (elem->data);
		if (monthday >= 0)
			recur_data->monthdays[monthday] = 1;
		else
			recur_data->neg_monthdays[-monthday] = 1;
		elem = elem->next;
	}


	elem = recur->byday;
	while (elem) {
		weekday = GPOINTER_TO_INT (elem->data);
		recur_data->weekdays[weekday] = 1;
		elem = elem->next;
	}


	elem = recur->byhour;
	while (elem) {
		hour = GPOINTER_TO_INT (elem->data);
		recur_data->hours[hour] = 1;
		elem = elem->next;
	}


	elem = recur->byminute;
	while (elem) {
		minute = GPOINTER_TO_INT (elem->data);
		recur_data->minutes[minute] = 1;
		elem = elem->next;
	}


	elem = recur->bysecond;
	while (elem) {
		second = GPOINTER_TO_INT (elem->data);
		recur_data->seconds[second] = 1;
		elem = elem->next;
	}
}
