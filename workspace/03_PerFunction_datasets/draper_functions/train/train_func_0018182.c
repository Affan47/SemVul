process_chains(void)
{
  vector<CHAIN*>::const_iterator p = chains_repp->begin();
  while(p != chains_repp->end()) {
    (*p)->process();
    ++p;
  }
}
