get_annotinfo (char *args, struct MGD77TRACK_ANNOT *info)
{
	int i1, i2, error = FALSE;
	int flag1, flag2, type;
	double value;

	info->annot_int_dist = info->tick_int_dist = 0;
	info->annot_int_time = info->tick_int_time = 0;

	i1 = 0;
	while (args[i1]) {
		flag1 = 'a';
		if (isalpha ((int)args[i1])) {
			flag1 = args[i1];
			if (isupper(flag1)) flag1 = tolower (flag1);
			i1++;
		}
		i2 = i1;
		while (args[i2] && strchr ("athkmnd", (int)args[i2]) == NULL) i2++;
		value = atof (&args[i1]);
		flag2 = args[i2];
		if (isupper(flag2)) flag2 = tolower (flag2);
		if (flag2 == 'd') {
			value *= GMT_DAY2SEC_F;
			type = 't';
		}
		else if (flag2 == 'h') {
			value *= GMT_HR2SEC_F;
			type = 't';
		}
		else if (flag2 == 'k') {
			value *= 1000;
			type = 'd';
		}
		else if (flag2 == 'n') {
			value *= MGD77_METERS_PER_NM;
			type = 'd';
		}
		else if (flag2 == 'm') {
			value *= GMT_MIN2SEC_F;
			type = 't';
		}
		else
			type = 't';
		i2++;
		if (flag1 == 'a') {
			if (type == 'd')
				info->annot_int_dist = (int)value;
			else
				info->annot_int_time = (int)value;
		}
		else {
			if (type == 'd')
				info->tick_int_dist = (int)value;
			else
				info->tick_int_time = (int)value;
		}
		i1 = i2;
	}
	if (info->annot_int_dist <= 0 && info->tick_int_dist <= 0 && info->annot_int_time <= 0 && info->tick_int_time <= 0)
		error = TRUE;
	if (info->annot_int_dist <= 0)
		info->annot_int_dist = info->tick_int_dist;
	else if (info->tick_int_dist <= 0)
		info->tick_int_dist = info->annot_int_dist;
	if (info->annot_int_time <= 0)
		info->annot_int_time = info->tick_int_time;
	else if (info->tick_int_time <= 0)
		info->tick_int_time = info->annot_int_time;
	return (error);
}
