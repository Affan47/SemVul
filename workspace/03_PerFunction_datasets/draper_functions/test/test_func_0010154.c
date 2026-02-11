stpi_calculate_row_parameters(void *vw,
			      int row,
			      int subpass,
			      int *pass,
			      int *jetnum,
			      int *startingrow,
			      int *ophantomrows,
			      int *ojetsused)
{
	cooked_t *w = (cooked_t *) vw;
	int raw_pass, jet, startrow, phantomrows, jetsused;
	int stagger = 0;
	int extra;

	STPI_ASSERT(row >= w->first_row_printed, w->rw.v);
	STPI_ASSERT(row <= w->last_row_printed, w->rw.v);
	calculate_raw_row_parameters(&w->rw,
	                             row + w->rw.separation * w->rw.jets,
	                             subpass, &raw_pass, &jet, &startrow);
	startrow -= w->rw.separation * w->rw.jets;
	jetsused = w->rw.jets;
	phantomrows = 0;

	if (raw_pass < w->first_normal_pass) {
	        STPI_ASSERT(raw_pass >= w->first_premapped_pass, w->rw.v);
		*pass = w->pass_premap[raw_pass - w->first_premapped_pass];
		stagger = w->stagger_premap[raw_pass - w->first_premapped_pass];
	} else if (raw_pass >= w->first_postmapped_pass) {
	        STPI_ASSERT(raw_pass >= w->first_postmapped_pass, w->rw.v);
		*pass = w->pass_postmap[raw_pass - w->first_postmapped_pass];
		stagger = w->stagger_postmap[raw_pass
		                             - w->first_postmapped_pass];
	} else {
		*pass = raw_pass - w->first_premapped_pass;
	}

	startrow += stagger * w->rw.separation;
	*jetnum = jet - stagger;
	if (stagger < 0) {
		stagger = -stagger;
		phantomrows += stagger;
	}
	jetsused -= stagger;

	extra = w->first_row_printed
	             - (startrow + w->rw.separation * phantomrows);
	if (extra > 0) {
		extra = (extra + w->rw.separation - 1) / w->rw.separation;
		jetsused -= extra;
		phantomrows += extra;
	}

	extra = startrow + w->rw.separation * (phantomrows + jetsused - 1)
	          - w->last_row_printed;
	if (extra > 0) {
		extra = (extra + w->rw.separation - 1) / w->rw.separation;
		jetsused -= extra;
	}

	*startingrow = startrow;
	*ophantomrows = phantomrows;
	*ojetsused = jetsused;
}
