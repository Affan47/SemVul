format_value(GB_VALUE * arg, DB_FORMAT_CALLBACK add)
{

#ifdef ODBC_DEBUG_HEADER
fprintf(stderr,"[ODBC][%s][%d]\n",__FILE__,__LINE__);
fprintf(stderr,"\tformat_value\n");
fflush(stderr);
#endif

	int l;
	GB_DATE_SERIAL *date;

	switch (arg->type)
	{
		case GB_T_BOOLEAN:


			if (VALUE((GB_BOOLEAN *) arg))
				add("'1'", 3);
			else
				add("'0'", 3);
			return TRUE;

		case GB_T_STRING:
		case GB_T_CSTRING:

			return FALSE;

		case GB_T_DATE:

			date = GB.SplitDate((GB_DATE *) arg);

			l = sprintf(_buffer, "'%04d-%02d-%02d-%02d.%02d.%02d",
									date->year, date->month, date->day,
									date->hour, date->min, date->sec);

			add(_buffer, l);

			if (date->msec)
			{
				l = sprintf(_buffer, ".%03d", date->msec);
				add(_buffer, l);
			}

			add("'", 1);

			return TRUE;

		default:
			return FALSE;
	}
}
