EncodeTimeOnly(struct pg_tm * tm, fsec_t fsec, bool print_tz, int tz, int style, char *str)
{
	sprintf(str, "%02d:%02d:", tm->tm_hour, tm->tm_min);
	str += strlen(str);

	AppendSeconds(str, tm->tm_sec, fsec, MAX_TIME_PRECISION, true);

	if (print_tz)
		EncodeTimezone(str, tz, style);
}
