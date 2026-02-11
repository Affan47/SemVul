flush_scrollback()
{
	int i;
	int result;
	for (i = 0; i <= video_num_lines; i++)
		result = write(1, "\n", 1);
}
