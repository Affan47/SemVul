gnumeric_unix2date (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float futime = value_get_as_float (argv [0]);
	time_t    utime  = (time_t)futime;
	gnm_float serial;


	if (gnm_abs (futime - utime) >= 1.0)
		return value_new_error_VALUE (ei->pos);

	serial = go_date_timet_to_serial_raw (utime, DATE_CONV (ei->pos));
	if (serial == G_MAXINT)
		return value_new_error_VALUE (ei->pos);

	return make_date (value_new_float (serial +
					   (futime - utime) / DAY_SECONDS));
}
