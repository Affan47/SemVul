create_hilites(linepos, start_index, end_index, chpos)
	POSITION linepos;
	int start_index;
	int end_index;
	int *chpos;
{
	struct hilite *hl;
	int i;


	hl = (struct hilite *) ecalloc(1, sizeof(struct hilite));
	hl->hl_startpos = linepos + chpos[start_index];


	for (i = start_index+1;  i <= end_index;  i++)
	{
		if (chpos[i] != chpos[i-1] + 1 || i == end_index)
		{
			hl->hl_endpos = linepos + chpos[i-1] + 1;
			add_hilite(&hilite_anchor, hl);

			if (i < end_index)
			{
				hl = (struct hilite *) ecalloc(1, sizeof(struct hilite));
				hl->hl_startpos = linepos + chpos[i];
			}
		}
	}
}
