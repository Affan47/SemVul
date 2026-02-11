MGD77_Read_Data_Record_txt (struct MGD77_CONTROL *F, struct MGD77_DATA_RECORD *MGD77Record)
{
	int i, j, n9, nwords, k, yyyy, mm, dd;
	GMT_LONG pos = 0;
	GMT_cal_rd rata_die;
	char line[BUFSIZ], p[BUFSIZ];
	double tz, secs;

	if (!(fgets (line, BUFSIZ, F->fp))) return (MGD77_ERROR_READ_ASC_DATA);
	GMT_chop (line);

	MGD77Record->bit_pattern = 0;
	for (i = k = nwords = 0; i < MGD77_N_DATA_FIELDS; i++) {
		if (!GMT_strtok (line, "\t", &pos, p)) return (MGD77_ERROR_READ_ASC_DATA);
		if (i >= MGD77_ID && i <= MGD77_SSPN) {
			strcpy (MGD77Record->word[nwords++], p);
			for (j = n9 = 0; p[j]; j++) if (p[j] == '9') n9++;
			if (n9 < j) MGD77Record->bit_pattern |= MGD77_this_bit[i];
		}
		else {
			MGD77Record->number[k] = (p[0] == 'N') ? GMT_d_NaN : atof (p);
			if (i == 0 && !(p[0] == '5' || p[0] == '3')) return (MGD77_NO_DATA_REC);
			if (!GMT_is_dnan (MGD77Record->number[k])) MGD77Record->bit_pattern |= MGD77_this_bit[i];
			k++;
		}
	}


	if ((MGD77Record->bit_pattern & MGD77_TIME_BITS) == MGD77_TIME_BITS) {
		yyyy = irint (MGD77Record->number[MGD77_YEAR]);
		mm = irint (MGD77Record->number[MGD77_MONTH]);
		dd = irint (MGD77Record->number[MGD77_DAY]);
		rata_die = GMT_rd_from_gymd (yyyy, mm, dd);
		tz = (GMT_is_dnan (MGD77Record->number[MGD77_TZ])) ? 0.0 : MGD77Record->number[MGD77_TZ];
		secs = GMT_HR2SEC_I * (MGD77Record->number[MGD77_HOUR] + tz) + GMT_MIN2SEC_I * MGD77Record->number[MGD77_MIN];
		MGD77Record->time = MGD77_rdc2dt (F, rata_die, secs);
		MGD77Record->bit_pattern |= MGD77_this_bit[MGD77_TIME];
	}
	else
		MGD77Record->time = GMT_d_NaN;
	return (MGD77_NO_ERROR);
}
