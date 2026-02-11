xxxqof_print_date_time_buff (char *buff, size_t len, time_t secs)
{
	int flen;
	int day, month, year, hour, min, sec;
	struct tm ltm, gtm;

	if (!buff)
		return 0;
	ltm = *localtime (&secs);
	day = ltm.tm_mday;
	month = ltm.tm_mon + 1;
	year = ltm.tm_year + 1900;
	hour = ltm.tm_hour;
	min = ltm.tm_min;
	sec = ltm.tm_sec;
	switch (qof_date_format_get_current ())
	{
	case QOF_DATE_FORMAT_UK:
		flen =
			g_snprintf (buff, len, "%2d/%2d/%-4d %2d:%02d", day, month,
			year, hour, min);
		break;
	case QOF_DATE_FORMAT_CE:
		flen =
			g_snprintf (buff, len, "%2d.%2d.%-4d %2d:%02d", day, month,
			year, hour, min);
		break;
	case QOF_DATE_FORMAT_ISO:
		flen =
			g_snprintf (buff, len, "%04d-%02d-%02d %02d:%02d", year, month,
			day, hour, min);
		break;
	case QOF_DATE_FORMAT_UTC:
		{
			gtm = *gmtime (&secs);
			flen = strftime (buff, len, QOF_UTC_DATE_FORMAT, &gtm);
			break;
		}
	case QOF_DATE_FORMAT_LOCALE:
		{
			flen = strftime (buff, len, QOF_D_T_FMT, &ltm);
		}
		break;

	case QOF_DATE_FORMAT_US:
	default:
		flen =
			g_snprintf (buff, len, "%2d/%2d/%-4d %2d:%02d", month, day,
			year, hour, min);
		break;
	}
	return flen;
}
