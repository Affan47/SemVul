process_inclusions (char *string, IIT_T chromosome_iit) {
  bool *includep;
  int nchromosomes, index, i;
  char *chrstring;


  nchromosomes = IIT_total_nintervals(chromosome_iit);
  includep = (bool *) CALLOC(nchromosomes,sizeof(bool));
  for (i = 0; i < nchromosomes; i++) {
    includep[i] = false;
  }

  while ((chrstring = get_next_token(&string)) != NULL) {
    debug(printf("Token is %s\n",chrstring));
    index = IIT_find_one(chromosome_iit,chrstring);
    includep[index-1] = true;
    FREE(chrstring);
  }
  return includep;
}
