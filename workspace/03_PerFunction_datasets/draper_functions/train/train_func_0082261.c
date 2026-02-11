est_cond_set_phrase(ESTCOND *cond, const char *phrase){
  assert(cond && phrase);
  if(cond->phrase) free(cond->phrase);
  while(*phrase > '\0' && *phrase <= ' '){
    phrase++;
  }
  cond->phrase = cbmemdup(phrase, -1);
}
