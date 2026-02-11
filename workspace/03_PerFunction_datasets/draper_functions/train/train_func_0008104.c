displayPosition(f_state *s, f_info *i, u_int64_t pos)
{

	int			percentDone = 0;
	static int	last_val = 0;
	int			count;
	int			flag = FALSE;
	int			factor = 4;
	int			multiplier = 25;
	int			number_of_stars = 0;
	char		buffer[256];
	long double skip = s->skip * s->block_size;

	long double tot_bytes = (long double)((i->total_bytes));
	tot_bytes -= skip;
	if (i->total_bytes > 0)
		{
		percentDone = (((long double)pos) / ((long double)tot_bytes)) * 100;
		if (percentDone != last_val)
			flag = TRUE;
		last_val = percentDone;
		}
	else
		{
		flag = TRUE;
		factor = 4;
		multiplier = 25;
		}

	if (flag)
		{
		number_of_stars = percentDone / factor;

		printf("%s: |", s->input_file);
		for (count = 0; count < number_of_stars; count++)
			{
			printf("*");
			}

		for (count = 0; count < (multiplier - number_of_stars); count++)
			{
			printf(" ");
			}

		if (i->total_bytes > 0)
			{
			printf("|\t %d%% done\n", percentDone);
			}
		else
			{
			printf("|\t %s done\n", human_readable(pos, buffer));

			}
		}

	if (percentDone == 100)
		{
		last_val = 0;
		}

	return TRUE;
}
