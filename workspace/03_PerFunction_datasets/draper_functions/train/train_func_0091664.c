zMakeEtermsFrom5(const zFeatureFactory *fac, coor_t pos, zSFList* sfl) {
	coor_t stop[3];
	coor_t end,max_end;
	int loh,frame;

	zSfeature* exon;
	if (pos < PADDING) return;

	if ((zGetUScore(fac->scan[ACC],pos-1) > MINIMUM_TWINSCAN_SIGNAL_SCORE)
		&& (pos > PADDING+43)){


		max_end = 0;
		for(loh = 0; loh < 3; loh++){
			stop[loh] = zGetStopSeqNextPos(fac->fstop,pos+loh)+2;
			if(stop[loh] > max_end){
				max_end = stop[loh];
			}
		}
		for(loh = 0; loh < 3; loh++){
			end = stop[loh];
			if(end > max_end) continue;

			if(end - pos + 1 < 6) continue;
			frame = (end-2) % 3;

			if ((zGetUScore(fac->scan[STOP],end-2) <= MINIMUM_TWINSCAN_SIGNAL_SCORE) ||
				(end-2 >= fac->scan[ACC]->seq->length-PADDING)) continue;


			exon = zSFListAppend(sfl);

			exon->group  = NULL;
			exon->strand = fac->strand;
			exon->name  = fac->type;
			exon->start = pos;
			exon->end   = end;
			exon->frame = frame;
			exon->lfrag = loh;
			exon->rfrag = 0;

			exon->score = fac->scoref(fac, exon);
		}
	}
}
