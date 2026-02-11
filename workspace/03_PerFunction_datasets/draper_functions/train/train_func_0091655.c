e_cal_component_get_start_plus_duration (ECalComponent *comp,
                                         ECalComponentDateTime *dt)
{
	ECalComponentPrivate *priv;
	struct icaldurationtype duration;

	priv = comp->priv;

	if (!priv->duration)
		return;


	get_datetime (&priv->dtstart, icalproperty_get_dtstart, dt);
	if (!dt->value)
		return;

	duration = icalproperty_get_duration (priv->duration);


	if (duration.is_neg)
		return;


	duration.days += duration.weeks * 7;
	if (dt->value->is_date) {
		if (duration.hours != 0 || duration.minutes != 0
		    || duration.seconds != 0) {
			dt->value->is_date = 0;
		}
	}


	icaltime_adjust (
		dt->value, duration.days, duration.hours,
		duration.minutes, duration.seconds);
}
