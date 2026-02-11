copy_all_tiles(void) {
	int x, y, n, m;
	int diffs = 0, ct;

	if (unixpw_in_progress) return 0;

	for (y=0; y < ntiles_y; y++) {
		for (x=0; x < ntiles_x; x++) {
			n = x + y * ntiles_x;

			if (tile_has_diff[n]) {
				ct = copy_tiles(x, y, 1);
				if (ct < 0) return ct;
			}
			if (! tile_has_diff[n]) {


				continue;
			}
			diffs++;


			if ( (y+1) < ntiles_y && tile_region[n].bot_diff) {
				m = x + (y+1) * ntiles_x;
				if (! tile_has_diff[m]) {
					tile_has_diff[m] = 2;
				}
			}

			if ( (x+1) < ntiles_x && tile_region[n].right_diff) {
				m = (x+1) + y * ntiles_x;
				if (! tile_has_diff[m]) {
					tile_has_diff[m] = 2;
				}
			}
		}
	}
	return diffs;
}
