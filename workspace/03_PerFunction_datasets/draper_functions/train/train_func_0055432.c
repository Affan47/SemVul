cal_obj_yearly_find_start_position (CalObjTime *event_start,
                                    CalObjTime *event_end,
                                    RecurData *recur_data,
                                    CalObjTime *interval_start,
                                    CalObjTime *interval_end,
                                    CalObjTime *cotime)
{
	*cotime = *event_start;


	if (cotime->year < interval_start->year) {
		gint years = interval_start->year - cotime->year
			+ recur_data->recur->interval - 1;
		years -= years % recur_data->recur->interval;

		cotime->year += years;
	}

	if ((event_end && cotime->year > event_end->year)
	    || (interval_end && cotime->year > interval_end->year))
		return TRUE;

	return FALSE;
}
