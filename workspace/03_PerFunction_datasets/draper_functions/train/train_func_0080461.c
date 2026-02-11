cache_sim_read_date(FILE *f, gchar *buf, gint s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 4 || strncmp("Date", buf, 4) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		gchar b;
		gchar buf[1024];
		gsize p = 0;

		b = 'X';
		while (b != '[')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}
		while (b != ']' && p < sizeof(buf) - 1)
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			buf[p] = b;
			p++;
			}

		while (b != '\n')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) break;
			}

		buf[p] = '\0';
		cd->date = strtol(buf, NULL, 10);

		cd->have_date = TRUE;

		return TRUE;
		}

	return FALSE;
}
