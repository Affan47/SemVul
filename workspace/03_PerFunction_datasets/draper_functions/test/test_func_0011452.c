inflate_seq_with_gaps(const ESL_ALPHABET *abc, char *src_str, int64_t src_len, int64_t dst_len, int *ngapA, char gapchar, char **ret_dst_str)
{
  int status;
  int src_apos = 0;
  int dst_apos  = 0;
  int src_flpos = 0;
  int src_frpos = 0;
  int i;
  char *dst_str;
  char char2add;
  int  i_am_fragment = FALSE;

  ESL_ALLOC(dst_str, sizeof(char) * (dst_len+1));
  dst_str[dst_len] = '\0';


  src_flpos = 0;
  while(src_flpos < src_len && esl_abc_CIsMissing(abc, src_str[src_flpos])) { src_flpos++; }
  src_flpos--;


  src_frpos = src_len-1;
  while(src_frpos > -1 && esl_abc_CIsMissing(abc, src_str[src_frpos])) { src_frpos--; }
  src_frpos++;


  i_am_fragment = (src_flpos != -1 || src_frpos != src_len) ? TRUE : FALSE;


  for(src_apos = src_flpos+1; src_apos <= src_frpos-1; src_apos++) {
    if(esl_abc_CIsMissing(abc, src_str[src_apos])) return eslEINVAL;
  }


  src_apos = 0;
  if(i_am_fragment) {
    char2add = ((src_flpos >= src_apos) || (src_frpos <= src_apos)) ? esl_abc_CGetMissing(abc) : gapchar;
  }
  else {
    char2add = gapchar;
  }
  if(ngapA) for(i = 0; i < ngapA[0]; i++) dst_str[dst_apos++] = char2add;


  for(src_apos = 0; src_apos < src_len; src_apos++) {
    dst_str[dst_apos++] = src_str[src_apos];
    if(i_am_fragment) {
      char2add = ((src_flpos >= src_apos) || (src_frpos <= src_apos)) ? esl_abc_CGetMissing(abc) : gapchar;
    }
    else {
      char2add = gapchar;
    }
    for(i = 0; i < ngapA[(src_apos+1)]; i++) dst_str[dst_apos++] = char2add;
  }

  *ret_dst_str = dst_str;
  return eslOK;

 ERROR:
  return eslEMEM;
}
