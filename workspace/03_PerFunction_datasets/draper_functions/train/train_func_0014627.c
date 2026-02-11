walk_tree(char **t, size_t max_y, size_t max_x, char *code, size_t code_size)
{
	int		 i;
	struct point	*p;

	if ((p = calloc(1, sizeof(struct point))) == NULL)
		err(2, "point calloc");


	if (getroot(t, p, max_x) != 0) {
		fprintf(stderr, "Terrible things happened.\n");
		return;
	}

	for (i = 0; i < code_size; i++) {
		int	isleaf;
		char	c;

		c = code[i];

		switch (c) {
		case '0':
			isleaf = step_left(t, p, max_x, max_y);
			if (isleaf == 1) {
				fprintf(stdout, "%c", t[p->y][p->x]);
				getroot(t, p, max_x);
			}
			break;
		case '1':
			isleaf = step_right(t, p, max_x, max_y);
			if (isleaf == 1) {
				fprintf(stdout, "%c", t[p->y][p->x]);
				getroot(t, p, max_x);
			}
			break;
		default:
			fprintf(stderr, "Problem with the given code (%c, %d).\n", c, c);
			break;
		}
	}
	fprintf(stdout, "\n");

	if (p)
		free(p);
}
