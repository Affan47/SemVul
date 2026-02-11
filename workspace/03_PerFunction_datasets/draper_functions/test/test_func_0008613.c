draw_rectangle(struct cave *c, int y1, int x1, int y2, int x2, int feat)
{
	int y, x;

	for (y = y1; y <= y2; y++) {
		cave_set_feat(c, y, x1, feat);
		cave_set_feat(c, y, x2, feat);
	}

	for (x = x1; x <= x2; x++) {
		cave_set_feat(c, y1, x, feat);
		cave_set_feat(c, y2, x, feat);
	}
}
