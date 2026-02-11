free_line(subtitle_line_t* sl)
{
    int i;
    for (i = 0; i < sl->lines; i++)
    {
	free(sl->line[i]);
	sl->line[i] = NULL;
    }
    sl->start = 0;
    sl->end = 0;
    sl->lines = 0;
}
