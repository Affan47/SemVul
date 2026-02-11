Stage3end_display_prep (Stage3end_T this, char *query, Compress_T query_compress_fwd, Compress_T query_compress_rev,
			Genome_T genome) {
  char *deletion_ignore;

  if (this != NULL) {
    debug0(printf("Doing a display prep of end %p\n",this));
    if (this->hittype == GMAP) {
      this->nmismatches_refdiff = this->nmismatches_bothdiff;

    } else if (this->hittype == DELETION) {
      this->nmismatches_refdiff =
	Substring_display_prep(&this->deletion,this->substring1,query,query_compress_fwd,query_compress_rev,
			       genome,this->indel_pos,
			       this->nindels);
    } else {
      this->nmismatches_refdiff =
	Substring_display_prep(&deletion_ignore,this->substring1,query,query_compress_fwd,query_compress_rev,
			       genome,-1,0);
    }

    if (this->substring2 != NULL) {
      this->nmismatches_refdiff +=
	Substring_display_prep(&deletion_ignore,this->substring2,query,query_compress_fwd,query_compress_rev,
			       genome,-1,0);
    }
    if (this->substring0 != NULL) {
      this->nmismatches_refdiff +=
	Substring_display_prep(&deletion_ignore,this->substring0,query,query_compress_fwd,query_compress_rev,
			       genome,-1,0);
    }
  }
  return;
}
