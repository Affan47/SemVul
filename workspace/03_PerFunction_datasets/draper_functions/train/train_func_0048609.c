prepareStats(const sentence_t& cand, const sentence_t& ref)
{
  vector<int> stats(2 * kMaxNOC);
  sentence_t intersection;

  set_intersection(cand.begin(), cand.end(), ref.begin(), ref.end(),
                   std::inserter(intersection, intersection.begin()));

  int multCoeff = 1000;

  for (int i = 0; i < 2 * kMaxNOC; ++i) stats[i] = 0;
  for (sentence_t::const_iterator it = intersection.begin(); it != intersection.end(); ++it) {
    const int sempos = it->second;
    float weight = semposScorer->weight(it->first);
    stats[2 * sempos] += weight * multCoeff ;
  }
  for (sentence_t::const_iterator it = ref.begin(); it != ref.end(); ++it) {
    const int sempos = it->second;
    float weight = semposScorer->weight(it->first);
    stats[2 * sempos + 1] += weight * multCoeff;
  }

  return stats;
}
