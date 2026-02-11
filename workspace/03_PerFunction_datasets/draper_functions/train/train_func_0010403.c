get_size_from_hints (AppletData *ad, int cells)
{
	int i;

	for (i = 0; i < ad->size_hints_len; i += 2) {
		if (cells > ad->size_hints[i]) {

			cells = ad->size_hints[i];
			break;
		}
		if (cells <= ad->size_hints[i] &&
		    cells >= ad->size_hints[i+1]) {

			break;
		}
	}

	return MAX (cells, ad->min_cells);
}
