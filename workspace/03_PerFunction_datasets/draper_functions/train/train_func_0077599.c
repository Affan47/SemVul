dpause(void)
{
	int ch;
	dfill(rows-1, 1, 0, columns, ' ', RED_RGBA, WHITE_RGBA);
	dprint(rows-1, 0, RED_RGBA, WHITE_RGBA, "Hit Q to quit, or any other key to continue...");
	while ((ch = display_getch(D, 1)) == ERROR_CHANGED)
		display_get_geometry(D, &rows, &columns);
	if (ch == 'q' || ch == 'Q') {
		display_end(D);
		exit(EXIT_SUCCESS);
	}
}
