read_oligos (T this, Sequence_T queryuc) {
  Reader_T reader;
  int querypos;
  Oligostate_T last_state = INIT;
#ifdef PMAP
  unsigned int aaindex = 0U;
#else
  Storedoligomer_T forward = 0U, revcomp = 0U;
#endif

  this->validp = (bool *) CALLOC(this->querylength,sizeof(bool));
#ifdef PMAP
  this->oligos = (Storedoligomer_T *) CALLOC(this->querylength,sizeof(Storedoligomer_T));
  reader = Reader_new(Sequence_fullpointer(queryuc),0,this->querylength);

  for (querypos = 0; querypos <= this->querylength - index1part_aa; querypos++) {
    this->validp[querypos] = false;
  }
#else
  this->forward_oligos = (Storedoligomer_T *) CALLOC(this->querylength,sizeof(Storedoligomer_T));
  this->revcomp_oligos = (Storedoligomer_T *) CALLOC(this->querylength,sizeof(Storedoligomer_T));
  reader = Reader_new(Sequence_fullpointer(queryuc),0,this->querylength);
  debug(printf("oligobase is %d, oligobase_mask is %08X\n",index1part,oligobase_mask));

  for (querypos = 0; querypos <= this->querylength - index1part; querypos++) {
    this->validp[querypos] = false;
  }
#endif


  while ((last_state = Oligo_next(last_state,&querypos,
#ifdef PMAP
				  &aaindex,
#else
				  &forward,&revcomp,
#endif
				  reader,FIVE)) != DONE) {

    this->validp[querypos] = true;
#ifdef PMAP
    this->oligos[querypos] = aaindex;
#else
    this->forward_oligos[querypos] = forward & oligobase_mask;
    this->revcomp_oligos[querypos] = (revcomp >> leftreadshift) & oligobase_mask;
#endif

#if 0
    if (this->forward_oligos[querypos] == 0U || this->revcomp_oligos[querypos] == 0U) {
      debug(printf("Position %d is poly-A or poly-T\n",querypos));
      this->polyat[querypos] = true;
    }
#endif

  }

  Reader_free(&reader);
  return;
}
