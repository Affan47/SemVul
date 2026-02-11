Shortread_find_overlap (T queryseq1, T queryseq2) {
  int overlap = 0;
  int nmatches, nmismatches;
  int fulllength1 = queryseq1->fulllength;
  int fulllength2 = queryseq2->fulllength;
  char *contents1 = queryseq1->contents_uc;
  char *contents2 = queryseq2->contents_uc;

  int best_score = 0, score;
  int istart, i, j;

  if (queryseq1->overlap >= 0) {
    return queryseq1->overlap;
  } else {
    debug2(printf("istart must be < %d - %d and < %d - %d\n",
		  fulllength1,OVERLAP_MINLENGTH,fulllength2,OVERLAP_MINLENGTH));
    for (istart = 0; istart < fulllength1 - OVERLAP_MINLENGTH && istart < fulllength2 - OVERLAP_MINLENGTH; istart++) {
      debug2(printf("istart = %d\n",istart));
      i = istart;
      j = 0;
      nmismatches = 0;
      while (nmismatches <= OVERLAP_NMISMATCHES_ALLOWED && i < fulllength1 - istart) {
	debug2(printf("At i = %d, j = %d, comparing %c and %c\n",i,j,contents1[i],contents2[j]));
	if (contents1[i] != contents2[j]) {
	  nmismatches++;
	}
	i++;
	j++;
      }
      if (nmismatches <= OVERLAP_NMISMATCHES_ALLOWED) {
	nmatches = j - nmismatches;
	if ((score = nmatches*3 - nmismatches) > best_score) {
	  best_score = score;
	  overlap = istart;
	}
      }
    }

    debug2(printf("overlap = %d\n",overlap));

    queryseq1->overlap = queryseq2->overlap = overlap;
    return overlap;
  }
}
