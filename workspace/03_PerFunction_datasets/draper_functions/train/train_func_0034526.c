tpg_alloc(struct tpg_data *tpg, unsigned max_w)
{
	unsigned pat;
	unsigned plane;

	tpg->max_line_width = max_w;
	for (pat = 0; pat < TPG_MAX_PAT_LINES; pat++) {
		for (plane = 0; plane < TPG_MAX_PLANES; plane++) {
			unsigned pixelsz = plane ? 2 : 4;

			tpg->lines[pat][plane] = vzalloc(max_w * 2 * pixelsz);
			if (!tpg->lines[pat][plane])
				return -ENOMEM;
			if (plane == 0)
				continue;
			tpg->downsampled_lines[pat][plane] = vzalloc(max_w * 2 * pixelsz);
			if (!tpg->downsampled_lines[pat][plane])
				return -ENOMEM;
		}
	}
	for (plane = 0; plane < TPG_MAX_PLANES; plane++) {
		unsigned pixelsz = plane ? 2 : 4;

		tpg->contrast_line[plane] = vzalloc(max_w * pixelsz);
		if (!tpg->contrast_line[plane])
			return -ENOMEM;
		tpg->black_line[plane] = vzalloc(max_w * pixelsz);
		if (!tpg->black_line[plane])
			return -ENOMEM;
		tpg->random_line[plane] = vzalloc(max_w * 2 * pixelsz);
		if (!tpg->random_line[plane])
			return -ENOMEM;
	}
	return 0;
}
