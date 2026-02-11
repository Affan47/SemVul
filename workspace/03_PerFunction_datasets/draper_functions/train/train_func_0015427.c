II_select_table(mpg123_handle *fr)
{
	const int translate[3][2][16] =
	{
		{
			{ 0,2,2,2,2,2,2,0,0,0,1,1,1,1,1,0 },
			{ 0,2,2,0,0,0,1,1,1,1,1,1,1,1,1,0 }
		},
		{
			{ 0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0 },
			{ 0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		},
		{
			{ 0,3,3,3,3,3,3,0,0,0,1,1,1,1,1,0 },
			{ 0,3,3,0,0,0,1,1,1,1,1,1,1,1,1,0 }
		}
	};

	int table,sblim;
	const struct al_table *tables[5] = { alloc_0, alloc_1, alloc_2, alloc_3 , alloc_4 };
	const int sblims[5] = { 27 , 30 , 8, 12 , 30 };

	if(fr->sampling_frequency >= 3)
	table = 4;
	else
	table = translate[fr->sampling_frequency][2-fr->stereo][fr->bitrate_index];

	sblim = sblims[table];
	fr->alloc      = tables[table];
	fr->II_sblimit = sblim;
}
