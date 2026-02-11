flush_lines(int nflush)
{
	LINE *l;

	while (--nflush >= 0) {
		l = lines;
		lines = l->l_next;
		if (l->l_line) {
			flush_blanks();
			flush_line(l);
		}
		nblank_lines++;
		if (l->l_line)
			free((void *)l->l_line);
		free_line(l);
	}
	if (lines)
		lines->l_prev = NULL;
}
