time2str(CS_TIME *t, CS_DATAFMT *srcfmt, char *buff, CS_INT len,
		int type, CS_LOCALE *locale) {
	if (type == 0) {
		CS_DATAFMT dstfmt;

		memset(&dstfmt, 0, sizeof(dstfmt));
		dstfmt.datatype = CS_CHAR_TYPE;
		dstfmt.maxlength = len;
		dstfmt.format = CS_FMT_NULLTERM;
		dstfmt.locale = locale;
		cs_convert(context, srcfmt, t, &dstfmt, buff, &len);

		return len - 1;
	} else {
		CS_DATEREC rec;
		cs_dt_crack(context, CS_TIME_TYPE, t, &rec);
		if (type == 2) {
			sprintf(buff, "%4.4d-%2.2d-%2.2dT%2.2d:%2.2d:%2.2d.%3.3dZ",
					rec.dateyear, rec.datemonth + 1, rec.datedmonth,
					rec.datehour, rec.dateminute, rec.datesecond,
					rec.datemsecond);
		} else {
			sprintf(buff, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%3.3d",
					rec.dateyear, rec.datemonth + 1, rec.datedmonth,
					rec.datehour, rec.dateminute, rec.datesecond,
					rec.datemsecond);
		}

		return strlen(buff);
	}

	return 0;
}
