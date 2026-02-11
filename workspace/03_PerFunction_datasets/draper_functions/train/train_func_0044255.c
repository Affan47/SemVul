restrict_to_block(BW *bw, SRCH *srch)
{
	if (!srch->valid || !srch->block_restrict)
		return 0;
	bw->cursor->xcol = piscol(bw->cursor);
	if (srch->backwards)
		if (!square) {
			if (bw->cursor->byte < srch->markb->byte)
				return 1;
			else if (bw->cursor->byte + sLEN(srch->entire) > srch->markk->byte)
				return -1;
		} else {
			if (bw->cursor->line < srch->markb->line)
				return 1;
			else if (bw->cursor->line > srch->markk->line)
				return -1;
			else if (piscol(bw->cursor) + sLEN(srch->entire) > srch->markk->xcol || piscol(bw->cursor) < srch->markb->xcol)
				return -1;
	} else if (!square) {
		if (bw->cursor->byte > srch->markk->byte)
			return 1;
		else if (bw->cursor->byte - sLEN(srch->entire) < srch->markb->byte)
			return -1;
	} else {
		if (bw->cursor->line > srch->markk->line)
			return 1;
		if (bw->cursor->line < srch->markb->line)
			return -1;
		if (piscol(bw->cursor) > srch->markk->xcol || piscol(bw->cursor) - sLEN(srch->entire) < srch->markb->xcol)
			return -1;
	}
	return 0;
}
