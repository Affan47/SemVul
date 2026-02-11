print_date(void)
{
	time_t now_time = time(NULL);

	if (params.commandline) {
		printf("%s", ctime(&now_time));
	} else {
		mvwprintw(text_win, main_ycord,
			  main_xcord, "%s",
			  slurm_ctime(&now_time));
		main_ycord++;
	}
}
