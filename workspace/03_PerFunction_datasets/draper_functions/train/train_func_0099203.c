init_arrays (void)
{
	int i;

	for (i=0; i< NUM_SPINES; i++)
	{
		kern_list[i] = NOTKERN;
		delta_list[i] = quarter;
		path_list[i] = NOTHING;
		chan_list[i] = 1;
		note_list[i].next = NULL;
	}
}
