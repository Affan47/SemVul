maze_pixmap_square_gen (int idx, char *col)
{
	int i, j;
	char **pixmap;
	char *line = "        ";
	pixmap = g_new(char *, MAZE_CELL_SIZE + 2);
	pixmap[0] = "8 8 1 1";
	pixmap[1] = g_strdup_printf (" c %s", col);
	for (i=0; i<MAZE_CELL_SIZE; i++) pixmap[i+2] = line; return pixmap;
}
