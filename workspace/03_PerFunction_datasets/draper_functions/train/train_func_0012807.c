Batch_init (Batch_T batch, int querypos, int diagterm, Genomicpos_T *positions, int npositions, int querylength) {

  batch->querypos = querypos;
  batch->diagterm = diagterm;
  batch->positions = positions;
#ifdef WORDS_BIGENDIAN
  batch->diagonal = Bigendian_convert_uint(*positions) + diagterm;
#else
  batch->diagonal = *positions + diagterm;
#endif
  batch->npositions = npositions;

  while (batch->npositions > 0 && batch->diagonal < (unsigned int) querylength) {
    debug11(printf("Eliminating diagonal %u as straddling beginning of genome (Batch_init)\n",batch->diagonal));
    batch->npositions--;
    if (batch->npositions > 0) {
#ifdef WORDS_BIGENDIAN
      batch->diagonal = Bigendian_convert_uint(*(++batch->positions)) + diagterm;
#else
      batch->diagonal = *(++batch->positions) + diagterm;
#endif
    }
  }


#ifdef HAVE_64_BIT
  batch->diagonal_add_querypos = (UINT8) batch->diagonal;
  batch->diagonal_add_querypos <<= 32;
  batch->diagonal_add_querypos |= querypos ;
#endif

  return;
}
