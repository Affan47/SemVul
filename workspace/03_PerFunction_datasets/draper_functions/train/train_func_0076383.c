pagedn(void)
{
	if (dmode == EXTENDED_MODE) {
		if ((edit_row[dmode] + dsplines) / lines_per_row[dmode] + 1 <=
		    end_row[dmode]) {
			start_row[dmode] += dsplines / lines_per_row[dmode];
			edit_row[dmode] += dsplines / lines_per_row[dmode];
		} else {
			edit_row[dmode] = end_row[dmode] - 1;
			while (edit_row[dmode] - start_row[dmode]
			       + 1 > last_entry_onscreen[dmode])
				start_row[dmode]++;
		}
	}
	else {
		start_row[dmode] = edit_row[dmode] = 0;
		if (dmode == GFS2_MODE ||
		    offset + screen_chunk_size >= sbd.bsize) {
			block++;
			offset = 0;
		} else
			offset += screen_chunk_size;
	}
}
