init_keyhashtab(VOID)
{
  unsigned i;
  int k,kmin,kmax;
  kmin = kmax = keywords[0].tclass;
  for(i=1; i<NUM_KEYWORDS; i++) {
    k = keywords[i].tclass;
    if(k < kmin)  kmin = k;
    if(k > kmax)  kmax = k;
  }

  keytab_offset = kmin;
  keytab_size = (unsigned) (kmax-kmin+1);
  if( (keytab_index=(short *)calloc(keytab_size,sizeof(keytab_index[0])))
     == (short *)NULL) {
    oops_message(OOPS_FATAL,NO_LINE_NUM,NO_COL_NUM,
	   "cannot allocate space for keytab_index");
  }


  for(i=0; i<NUM_KEYWORDS; i++) {
    k = keywords[i].tclass;
    keytab_index[k - keytab_offset] = i;
  }
}
