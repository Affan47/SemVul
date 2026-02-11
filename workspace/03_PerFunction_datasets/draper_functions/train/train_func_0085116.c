zMakeEsnglsFrom3 (const zFeatureFactory *fac, coor_t pos, zSFList* sfl) {
	coor_t i, begin, end;
	int frame;
	zSfeature* exon;

	if(pos < PADDING) return;

	if (zGetUScore(fac->scan[STOP],pos-2) > MINIMUM_TWINSCAN_SIGNAL_SCORE) {
		frame = (pos+1) % 3;


		end   = pos - 8;
		begin = zGetStopSeqPrevPos(fac->fstop,pos-5)+3;

		for (i = end; i >= begin; i -= 3) {
			if (zGetUScore(fac->scan[START],i) <= MINIMUM_TWINSCAN_SIGNAL_SCORE)
				continue;


			exon = zSFListAppend(sfl);

			exon->group  = NULL;
			exon->strand = fac->strand;
			exon->name  = fac->type;
			exon->start = i;
			exon->end   = pos;
			exon->lfrag = 0;
			exon->rfrag = 0;
			exon->frame = frame;

			exon->score = fac->scoref(fac, exon);
		}
	}
}
