board_print_top(struct board *board, char *s, char *end, int c)
{
	for (int i = 0; i < c; i++) {
		char asdf[] = "ABCDEFGHJKLMNOPQRSTUVWXYZ";
		s += snprintf(s, end - s, "      ");
		for (int x = 1; x < board_size(board) - 1; x++)
			s += snprintf(s, end - s, "%c ", asdf[x - 1]);
		s += snprintf(s, end -s, " ");
	}
	s += snprintf(s, end - s, "\n");
	for (int i = 0; i < c; i++) {
		s += snprintf(s, end - s, "    +-");
		for (int x = 1; x < board_size(board) - 1; x++)
			s += snprintf(s, end - s, "--");
		s += snprintf(s, end - s, "+");
	}
	s += snprintf(s, end - s, "\n");
	return s;
}
