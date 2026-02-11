e_cal_recur_ical_weekday_to_weekday (enum icalrecurrencetype_weekday day)
{
	gint weekday;

	switch (day) {
	case ICAL_NO_WEEKDAY:
	case ICAL_MONDAY_WEEKDAY:
		weekday = 0;
		break;
	case ICAL_TUESDAY_WEEKDAY:
		weekday = 1;
		break;
	case ICAL_WEDNESDAY_WEEKDAY:
		weekday = 2;
		break;
	case ICAL_THURSDAY_WEEKDAY:
		weekday = 3;
		break;
	case ICAL_FRIDAY_WEEKDAY:
		weekday = 4;
		break;
	case ICAL_SATURDAY_WEEKDAY:
		weekday = 5;
		break;
	case ICAL_SUNDAY_WEEKDAY:
		weekday = 6;
		break;
	default:
		g_warning (
			"e_cal_recur_ical_weekday_to_weekday(): Unknown week day %d",
			day);
		weekday = 0;
	}

	return weekday;
}
