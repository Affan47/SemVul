set(const char *n,string &v) {
  vector<PGNpair *>::iterator li;
  for(li=header.begin();li!=header.end();li++)
    if ( (*li)->name == n ) {
      (*li)->value = v;
      return;
    }
  header.push_back(new PGNpair(n,v));
}
