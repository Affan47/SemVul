join_regions(struct cave *c, int colors[], int counts[]) {
	int h = c->height;
	int w = c->width;
	int size = h * w;
	int num = count_colors(counts, size);

	while (num > 1) {
		int color = first_color(counts, size);
		join_region(c, colors, counts, color);
		num--;
	}
}
