BuildAllStates() {
  if (!ok())
    return 0;


  RWLocker l(&cache_mutex_);
  SearchParams params(NULL, NULL, &l);
  params.anchored = true;
  params.want_earliest_match = true;
  params.run_forward = true;
  if (!AnalyzeSearch(&params) || params.start <= SpecialStateMax)
    return 0;


  StateSet queued;
  vector<State*> q;
  queued.insert(params.start);
  q.push_back(params.start);


  for (int i = 0; i < q.size(); i++) {
    State* s = q[i];
    for (int c = 0; c < 257; c++) {
      State* ns = RunStateOnByteUnlocked(s, c);
      if (ns > SpecialStateMax && queued.find(ns) == queued.end()) {
        queued.insert(ns);
        q.push_back(ns);
      }
    }
  }

  return q.size();
}
