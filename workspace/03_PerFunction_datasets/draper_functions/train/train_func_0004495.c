build_colors(struct cave *c, int colors[], int counts[], bool diagonal) {
	int y, x;
	int h = c->height;
	int w = c->width;
	int color = 1;

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			if (ignore_point(cave, colors, y, x)) continue;
			build_color_point(cave, colors, counts, y, x, color, diagonal);
			color++;
		}
	}
}
