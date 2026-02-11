get_total_zu_count ()
{
	gchar tmpstr[256];
	gint i, total_zucount = 0, max_wordcount = 0, last_zu_wordcount =
		25, tmpint;

	for (i = 0; i <= g_pReciteWord->max_zu_index; i++)
	{
		sprintf (tmpstr, "zu%d_wordcount", i);
		if (rw_cfg_read_int
		    (usercfgfile, g_pReciteWord->now_book->bookfilename,
		     tmpstr, &tmpint))
			last_zu_wordcount = tmpint;
		max_wordcount += last_zu_wordcount;
	}
	max_wordcount -= last_zu_wordcount;

	total_zucount = g_pReciteWord->max_zu_index;

	total_zucount +=
		((g_pReciteWord->now_book->wordcount -
		  max_wordcount) / last_zu_wordcount);
	tmpint = (g_pReciteWord->now_book->wordcount -
		  max_wordcount) % last_zu_wordcount;

	if (tmpint>=6)
		total_zucount++;
	return total_zucount;
}
