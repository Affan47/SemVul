open_count(struct cave *c) {
	int x, y;
	int h = c->height;
	int w = c->width;
	int num = 0;
	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
			if (cave_ispassable(c, y, x)) num++;
	return num;
}
