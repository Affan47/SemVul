add_to_history(histype, new_entry, in_map, sep)
    int		histype;
    char_u	*new_entry;
    int		in_map;
    int		sep;
{
    histentry_T	*hisptr;
    int		len;

    if (hislen == 0)
	return;


    if (histype == HIST_SEARCH && in_map)
    {
	if (maptick == last_maptick)
	{

	    hisptr = &history[HIST_SEARCH][hisidx[HIST_SEARCH]];
	    vim_free(hisptr->hisstr);
	    hisptr->hisstr = NULL;
	    hisptr->hisnum = 0;
	    --hisnum[histype];
	    if (--hisidx[HIST_SEARCH] < 0)
		hisidx[HIST_SEARCH] = hislen - 1;
	}
	last_maptick = -1;
    }
    if (!in_history(histype, new_entry, TRUE))
    {
	if (++hisidx[histype] == hislen)
	    hisidx[histype] = 0;
	hisptr = &history[histype][hisidx[histype]];
	vim_free(hisptr->hisstr);


	len = (int)STRLEN(new_entry);
	hisptr->hisstr = vim_strnsave(new_entry, len + 2);
	if (hisptr->hisstr != NULL)
	    hisptr->hisstr[len + 1] = sep;

	hisptr->hisnum = ++hisnum[histype];
	if (histype == HIST_SEARCH && in_map)
	    last_maptick = maptick;
    }
}
