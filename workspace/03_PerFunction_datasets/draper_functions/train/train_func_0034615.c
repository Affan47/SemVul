print_hmminfo(char *name, HTK_HMM_INFO *hmminfo)
{
  HMM_Logical *l;

  l = htk_hmmdata_lookup_logical(hmminfo, name);
  if (l == NULL) {
    printf("no HMM named \"%s\"\n", name);
  } else {
    put_logical_hmm(stdout, l);
  }
}
