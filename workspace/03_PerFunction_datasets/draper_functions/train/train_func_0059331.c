add_table_padding(char **t, size_t y, size_t x, char padding)
{
	int i, j;

	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++) {
			if (iscntrl(t[i][j]) || t[i][j] == ' ')
				t[i][j] = padding;
		}
	}
}
