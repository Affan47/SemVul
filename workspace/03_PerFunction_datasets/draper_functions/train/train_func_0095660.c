e_cal_recur_ensure_rule_end_date (ECalComponent *comp,
                                  icalproperty *prop,
                                  gboolean exception,
                                  gboolean refresh,
                                  ECalRecurResolveTimezoneFn tz_cb,
                                  gpointer tz_cb_data)
{
	struct icalrecurrencetype rule;
	ECalRecurEnsureEndDateData cb_data;

	if (exception)
		rule = icalproperty_get_exrule (prop);
	else
		rule = icalproperty_get_rrule (prop);


	if (rule.count == 0)
		return FALSE;


	if (!refresh) {
		if (e_cal_recur_get_rule_end_date (prop, NULL) != -1)
			return FALSE;
	}


	cb_data.count = rule.count;
	cb_data.instances = 0;
	cb_data.end_date = 0;
	e_cal_recur_generate_instances_of_rule (
		comp, prop, -1, -1,
		e_cal_recur_ensure_rule_end_date_cb,
		&cb_data, tz_cb, tz_cb_data,
		icaltimezone_get_utc_timezone ());


	e_cal_recur_set_rule_end_date (prop, cb_data.end_date);

	return TRUE;
}
