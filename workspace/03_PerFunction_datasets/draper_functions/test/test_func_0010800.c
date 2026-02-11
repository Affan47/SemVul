gnumeric_minute (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	int secs = datetime_value_to_seconds (argv[0], DATE_CONV (ei->pos));

	if (secs < 0)
		return value_new_error_NUM (ei->pos);
	else
		return value_new_int (secs / 60 % 60);
}
