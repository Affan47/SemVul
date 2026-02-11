zMakeEncsFrom5 (const zFeatureFactory *fac, coor_t pos, zSFList* sfl) {
    coor_t i;
	zSfeature* exon;


	if (pos < PADDING + 40) return;

	if (zGetUScore(fac->scan[ACC],pos-1) > MINIMUM_TWINSCAN_SIGNAL_SCORE){

		for(i = pos + 5; i < pos + MAX_ENC_LENGTH;i++){
			if(zGetUScore(fac->scan[DON],i+1) > MINIMUM_TWINSCAN_SIGNAL_SCORE){
				exon = zSFListAppend(sfl);

				exon->group  = NULL;
				exon->strand = fac->strand;
				exon->name   = fac->type;
				exon->start  = pos;
				exon->end    = i;
				exon->lfrag  = 0;
				exon->rfrag  = 0;
				exon->frame  = 0;

				exon->score  = fac->scoref(fac, exon);
			}
		}
	}
}
