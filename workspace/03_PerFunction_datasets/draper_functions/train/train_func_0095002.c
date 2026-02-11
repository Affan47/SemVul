p_init_percents(struct file_info *info)
{
#ifdef WIN32_USE_CURSOR
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	percents.hOut = NULL;
#endif

	(void)info;
	percents.points      = 0;
	percents.same_output = 0;
	percents.use_cursor  = 0;

	fflush(rhash_data.out);
	fflush(rhash_data.log);
	assert(rhash_data.log == stderr);


	fprintf(rhash_data.log, "%-51s ", info->print_path);

#ifdef WIN32_USE_CURSOR
	if(percents.use_cursor) {

		percents.hOut = GetStdHandle(STD_ERROR_HANDLE);
		if(percents.hOut == INVALID_HANDLE_VALUE ||
			!GetConsoleScreenBufferInfo(percents.hOut, &csbInfo)) {
				percents.hOut = NULL;
				return 0;
		} else {
			percents.cur_x = csbInfo.dwCursorPosition.X;
			percents.cur_y = csbInfo.dwCursorPosition.Y;
		}
	}
#endif

	percents.same_output = (rhash_data.out == stdout && isatty(0));
	percents.ticks = rhash_get_ticks();
	return 1;
}
