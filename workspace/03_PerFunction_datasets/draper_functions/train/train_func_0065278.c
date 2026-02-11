unwrap_timestamp(struct iax_frame *fr)
{


	const int ts_shift = (fr->af.frametype == AST_FRAME_VIDEO) ? 15 : 16;
	const int lower_mask = (1 << ts_shift) - 1;
	const int upper_mask = ~lower_mask;
	const int last_upper = iaxs[fr->callno]->last & upper_mask;

	if ( (fr->ts & upper_mask) == last_upper ) {
		const int x = fr->ts - iaxs[fr->callno]->last;
		const int threshold = (ts_shift == 15) ? 25000 : 50000;

		if (x < -threshold) {


			fr->ts = (last_upper + (1 << ts_shift)) | (fr->ts & lower_mask);
			if (iaxdebug)
				ast_debug(1, "schedule_delivery: pushed forward timestamp\n");
		} else if (x > threshold) {


			fr->ts = (last_upper - (1 << ts_shift)) | (fr->ts & lower_mask);
			if (iaxdebug)
				ast_debug(1, "schedule_delivery: pushed back timestamp\n");
		}
	}
}
