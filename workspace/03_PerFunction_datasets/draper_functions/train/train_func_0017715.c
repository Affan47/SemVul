day_bin (GttInterval *ivl, gpointer data)
{
	DayArray *da = data;
	time_t start, start_off, stop, end_of_day;
	struct tm stm;
	int century_day, arr_day;
	GttTask *tsk;

	tsk = gtt_interval_get_parent (ivl);
	start = gtt_interval_get_start (ivl);
	stop = gtt_interval_get_stop (ivl);


	start_off = start - config_daystart_offset;
	localtime_r (&start_off, &stm);
	century_day = yearday_to_centuryday (stm.tm_yday, stm.tm_year);
	arr_day = century_day - da->start_cday;


	stm.tm_sec = 0;
	stm.tm_min = 0;
	stm.tm_hour = 0;

	while (1)
	{

		if ((0 > arr_day) || (arr_day >= da->array_len))
		{
			return 1;
		}
		GttBucket *bu;
		bu = &g_array_index (da->buckets, GttBucket, arr_day);

		stm.tm_mday ++;
		end_of_day = mktime (&stm);

		end_of_day += config_daystart_offset;

		if (stop < end_of_day)
		{
			bu->total += stop - start;
			bu->intervals = g_list_append (bu->intervals, ivl);


			if (!bu->tasks || (bu->tasks->data != tsk))
			{
				bu->tasks = g_list_prepend (bu->tasks, tsk);
			}
			return 1;
		}
		else
		{
			bu->total+= end_of_day - start;
			bu->intervals = g_list_append (bu->intervals, ivl);


			if (!bu->tasks || (bu->tasks->data != tsk))
			{
				bu->tasks = g_list_prepend (bu->tasks, tsk);
			}
		}
		arr_day ++;
		start = end_of_day;
	}

	return 1;
}
