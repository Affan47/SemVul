icaltimetype_to_tm_with_zone (struct icaltimetype *itt,
                              icaltimezone *from_zone,
                              icaltimezone *to_zone)
{
	struct tm tm;
	struct icaltimetype itt_copy;

	memset (&tm, 0, sizeof (tm));
	tm.tm_isdst = -1;

	g_return_val_if_fail (itt != NULL, tm);

	itt_copy = *itt;

	icaltimezone_convert_time (&itt_copy, from_zone, to_zone);
	tm = icaltimetype_to_tm (&itt_copy);

	return tm;
}
