Pair_nmatches_posttrim (int *max_match_length, List_T pairs, int pos5, int pos3) {
  int nmatches = 0, match_length;
  bool in_intron = false, indelp = false;
  List_T p;
  T this;

  *max_match_length = match_length = 0;
  for (p = pairs; p != NULL; p = p->rest) {
    this = p->first;
    if (this->gapp) {
      if (!in_intron) {
	in_intron = true;
      }
    } else {
      if (in_intron) {
	in_intron = false;
      }
      if (this->comp == INDEL_COMP || this->comp == SHORTGAP_COMP) {
	indelp = true;
#ifndef PMAP
      } else if (unknown_base(this->cdna) || unknown_base(this->genome) || this->comp == AMBIGUOUS_COMP) {

#endif
      } else if (this->querypos < pos5) {

      } else if (this->querypos >= pos3) {

      } else if (this->comp == MATCH_COMP || this->comp == DYNPROG_MATCH_COMP || this->comp == AMBIGUOUS_COMP) {
	nmatches++;
	match_length++;
      } else if (this->comp == MISMATCH_COMP) {

	if (match_length > *max_match_length) {
	  *max_match_length = match_length;
	}
	match_length = 0;
      } else {
	fprintf(stderr,"Can't parse comp %c, gapp %d\n",this->comp,this->gapp);
	abort();
      }
    }
  }

  if (match_length > *max_match_length) {
    *max_match_length = match_length;
  }

  return nmatches;
}
