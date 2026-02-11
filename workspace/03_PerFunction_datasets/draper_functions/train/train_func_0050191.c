gt_reads2twobit_init_encode(GtReads2Twobit *r2t,
    GtReads2TwobitEncodeState *state)
{
  const unsigned long noflibraries = gt_array_size(r2t->collection);
  unsigned long i;
  state->inputfiles_totallength = 0;
  for (i = 0; i < noflibraries; i++)
  {
    const GtReadsLibraryInfo *rli = gt_array_get(r2t->collection, i);
    state->inputfiles_totallength += rli->total_filelength;
  }
  r2t->twobitencoding = gt_malloc(sizeof (*r2t->twobitencoding) *
    GT_DIVBYUNITSIN2BITENC(state->inputfiles_totallength) + 2UL);
  GT_READS2TWOBIT_INIT_ENCODE_INFO(state->current, r2t->twobitencoding);
  GT_READS2TWOBIT_COPY_ENCODE_INFO(state->current, state->backup);
  for (i = 0; i < (unsigned long)(UCHAR_MAX) + 1UL; i++)
    state->char2code[i] = GT_READS2TWOBIT_CODE_UNDEF;
  state->char2code[(unsigned char)'A'] = (GtTwobitencoding)0;
  state->char2code[(unsigned char)'a'] = (GtTwobitencoding)0;
  state->char2code[(unsigned char)'C'] = (GtTwobitencoding)1;
  state->char2code[(unsigned char)'c'] = (GtTwobitencoding)1;
  state->char2code[(unsigned char)'G'] = (GtTwobitencoding)2;
  state->char2code[(unsigned char)'g'] = (GtTwobitencoding)2;
  state->char2code[(unsigned char)'T'] = (GtTwobitencoding)3;
  state->char2code[(unsigned char)'t'] = (GtTwobitencoding)3;
  state->seqlen = 0;
  state->seqlen_mate = 0;
  state->seqlen_first = 0;
  state->varlen_mode = false;
  state->invalid_mode = false;
  state->invalid_sequences = 0;
  state->invalid_total_length = 0;
  gt_assert(r2t->seppos == NULL);
  state->seppos = NULL;
  state->qbuf = NULL;
  state->qbuf_size = 0;
  state->qbuf2 = NULL;
  state->qbuf2_size = 0;
  state->phredbase = r2t->phredbase;
  state->lowqual = r2t->lowqual;
  state->maxlow = r2t->maxlow;
}
