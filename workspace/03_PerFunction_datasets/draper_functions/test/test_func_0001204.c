set_span(int total,  uint16_t tree_width)
{
	int *span = NULL;
	int left = total;
	int i = 0;

	if (tree_width == 0)
		tree_width = slurm_get_tree_width();

	span = xmalloc(sizeof(int) * tree_width);

	if (total <= tree_width) {
		return span;
	}

	while (left > 0) {
		for(i = 0; i < tree_width; i++) {
			if ((tree_width-i) >= left) {
				if (span[i] == 0) {
					left = 0;
					break;
				} else {
					span[i] += left;
					left = 0;
					break;
				}
			} else if (left <= tree_width) {
				span[i] += left;
				left = 0;
				break;
			}
			span[i] += tree_width;
			left -= tree_width;
		}
	}
	return span;
}
