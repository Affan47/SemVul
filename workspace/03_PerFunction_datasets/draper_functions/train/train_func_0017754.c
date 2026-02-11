get(const char *n) {
  vector<PGNpair *>::iterator li;

  for(li=header.begin();li!=header.end();li++) {
    if ( (*li)->name == n )
      return((*li)->value.c_str());
  }
  return 0;
}
