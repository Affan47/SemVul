zMakeEpasFromInside (const zFeatureFactory *fac, coor_t pos, zSFList* sfl) {
	coor_t begin, end;
	zSfeature* exon;
	if (pos < PADDING) return;

	for(end = pos; end < pos + MAX_EPA_LENGTH; end++){
		if (zGetUScore(fac->scan[START],end+1) > MINIMUM_TWINSCAN_SIGNAL_SCORE) {
			begin = end - MAX_EPA_LENGTH + 1;
			if(end  < PADDING + MAX_EPA_LENGTH - 1){
				begin = PADDING;
			}
			else{
				begin = end - MAX_EPA_LENGTH + 1;
			}

			for(;begin < end - 4; begin++){
				exon = zSFListAppend(sfl);
				exon->group  = NULL;
				exon->strand = fac->strand;
				exon->name   = fac->type;
				exon->start  = begin;
				exon->end    = end;
				exon->lfrag  = 0;
				exon->rfrag  = 0;
				exon->frame  = 0;

				exon->score  = fac->scoref(fac, exon);

			}
		}
	}
}
