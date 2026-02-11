print_high_scores()
{
	if(!highs)
	{
		log_printf(WLOG, "No hiscore entries found!\n");
		return;
	}

	log_printf(ULOG, "Name                     Score Start End\n");
	for(unsigned int j = 0; j < highs; j++)
	{
		log_printf(ULOG, "%-20s %9u %5d %3d\n", high_tbl[j].name,
				high_tbl[j].score,
				high_tbl[j].start_scene,
				high_tbl[j].end_scene);
	}
}
