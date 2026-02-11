kaakp_pctoindex (const SQUARE *pw, const SQUARE *pb, index_t *out)
{
	enum 	{BLOCK_C = MAX_AAINDEX
			,BLOCK_B = 64*BLOCK_C
			,BLOCK_A = 64*BLOCK_B
	};
	index_t aa_combo, pslice;

	SQUARE wk   = pw[0];
	SQUARE wa   = pw[1];
	SQUARE wa2  = pw[2];
	SQUARE bk   = pb[0];
	SQUARE pawn = pb[1];

	assert (A2 <= pawn && pawn < A8);

	if ((pawn & 07) > 3) {
		pawn = flipWE (pawn);
		wk   = flipWE (wk);
		bk   = flipWE (bk);
		wa   = flipWE (wa);
		wa2  = flipWE (wa2);
	}

	pawn = flipNS(pawn);
	pslice = wsq_to_pidx24 (pawn);

	aa_combo = (index_t)aaidx [wa] [wa2];

	if (IDX_is_empty(aa_combo)) {
		*out = NOINDEX;
		return FALSE;
	}

	*out = pslice * (index_t)BLOCK_A + (index_t)wk * (index_t)BLOCK_B  + (index_t)bk * (index_t)BLOCK_C + aa_combo;

	assert (*out >= 0);

	return TRUE;
}
