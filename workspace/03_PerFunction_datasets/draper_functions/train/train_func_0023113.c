zMakeEinitsFromInside(const zFeatureFactory *fac, coor_t pos, zSFList* sfl) {
	coor_t i, j, begin, end, min_end, max_end, min_begin;
	coor_t start[3];
	coor_t stop[3];
	int frame;

	zSfeature* exon;
	if (pos < PADDING) return;

	max_end = 0;
	min_begin = fac->dna->length;
	for(frame = 0;frame <= 2;frame++){
		stop[frame]  = zGetStopSeqNextPos(fac->fstop,pos-frame)+2;
		start[frame] = zGetStopSeqPrevPos(fac->fstop,stop[frame]-2-3)+3;
		if(max_end < stop[frame]){
			max_end = stop[frame];
		}
		if(min_begin > start[frame]){
			min_begin = start[frame];
		}
	}


	for(frame = 0;frame <= 2;frame++){
		begin = start[frame];
		end = stop[frame];

		if(begin < min_begin){
			begin = min_begin;
		}
		if(end > max_end){
			end = max_end;
		}

		for(i = pos;i >= begin;i-=3){
			if(zGetUScore(fac->scan[START],i) <= MINIMUM_TWINSCAN_SIGNAL_SCORE)
				continue;
			min_end = pos;

			if(min_end < i+2){
				min_end = i+2;
			}
			for(j = min_end; j < end; j++){
				if (zGetUScore(fac->scan[DON],j+1) <= MINIMUM_TWINSCAN_SIGNAL_SCORE)
					continue;


				exon = zSFListAppend(sfl);

				exon->group  = NULL;
				exon->strand = fac->strand;
				exon->name  = fac->type;
				exon->start = i;
				exon->end   = j;
				exon->lfrag = 0;
				exon->rfrag = (exon->end - exon->start + 1) % 3;
				exon->frame = exon->start % 3;

				exon->score = fac->scoref(fac, exon);
			}
		}
	}
}
