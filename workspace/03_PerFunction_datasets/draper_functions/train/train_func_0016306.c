most_specific_oligomer_1 (int *best_plus_querypos, int *best_minus_querypos, T this,
			  int query_lastpos, Indexdb_T indexdb_fwd, Indexdb_T indexdb_rev) {
  int querypos;
  int best_plus_count, best_minus_count;


  best_plus_querypos[0] = -1;
  best_minus_querypos[0] = -1;

  best_plus_count = 0;
  best_minus_count = 0;

  for (querypos = 0; querypos <= query_lastpos; querypos++) {
#if 0
    if (this->validp[querypos] == true) {
#endif
      this->plus_npositions[querypos] = Indexdb_count_no_subst(indexdb_fwd,this->forward_oligos[querypos]);
      this->minus_npositions[querypos] = Indexdb_count_no_subst(indexdb_rev,this->revcomp_oligos[querypos]);
      debug(printf("Counting at querypos %d, plus_npositions = %d (oligo %06X), minus_npositions = %d (oligo %06X)\n",
		   querypos,this->plus_npositions[querypos],this->forward_oligos[querypos],
		   this->minus_npositions[querypos],this->revcomp_oligos[querypos]));

      if (best_plus_querypos[0] < 0 || this->plus_npositions[querypos] < best_plus_count) {
	best_plus_querypos[0] = querypos;
	best_plus_count = this->plus_npositions[querypos];
      }
      if (best_minus_querypos[0] < 0 || this->minus_npositions[querypos] < best_minus_count) {
	best_minus_querypos[0] = querypos;
	best_minus_count = this->minus_npositions[querypos];
      }
#if 0
    }
#endif
  }

  return;
}
