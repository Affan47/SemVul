highscore_where(const high_score *entry, const high_score scores[], size_t sz)
{
	size_t i;


	for (i = 0; i < sz; i++)
	{
		long entry_pts = strtoul(entry->pts, NULL, 0);
		long score_pts = strtoul(scores[i].pts, NULL, 0);

		if (entry_pts >= score_pts)
			return i;

		if (scores[i].what[0] == '\0')
			return i;
	}


	return sz - 1;
}
