blkchk(BLOCK *blk)
{


	if ((conf->calc_debug & CALCDBG_BLOCK) == 0) {

		return;
	}
	if (blk == NULL) {
		math_error("internal: blk ptr is NULL");

	}


	if (blk->data == NULL) {
		math_error("internal: blk->data ptr is NULL");

	}


	if (blk->datalen < 0) {
		math_error("internal: blk->datalen < 0");

	}


	if (blk->datalen < 0) {
		math_error("internal: blk->datalen < 0");

	}
	return;
}
