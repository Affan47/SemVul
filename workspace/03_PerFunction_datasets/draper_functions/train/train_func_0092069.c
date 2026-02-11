gapize_string(char *src_str, int64_t src_len, int64_t dst_len, int *ngapA, char gapchar, char **ret_dst_str)
{
  int status;
  int src_apos = 0;
  int dst_apos  = 0;
  int i;
  char *dst_str;

  ESL_ALLOC(dst_str, sizeof(char) * (dst_len+1));
  dst_str[dst_len] = '\0';


  for(i = 0; i < ngapA[0]; i++) dst_str[dst_apos++] = gapchar;


  for(src_apos = 0; src_apos < src_len; src_apos++) {
    dst_str[dst_apos++] = src_str[src_apos];
    for(i = 0; i < ngapA[(src_apos+1)]; i++) dst_str[dst_apos++] = gapchar;
  }

  *ret_dst_str = dst_str;
  return eslOK;

 ERROR:
  return eslEMEM;
}
