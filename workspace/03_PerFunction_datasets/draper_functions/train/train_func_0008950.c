zip_make_modtime (guint32 dostime)
{
	if (dostime == 0)
		return NULL;
	else {
		gint year = (dostime >> 25) + 1980;
		gint month = (dostime >> 21) & 0x0f;
		gint day = (dostime >> 16) & 0x1f;
		gint hour = (dostime >> 11) & 0x0f;
		gint minute = (dostime >> 5) & 0x3f;
		gint second = (dostime & 0x1f) * 2;
		GDateTime *modtime =
			g_date_time_new_utc (year, month, day,
					     hour, minute, second);
		return modtime;
	}
}
