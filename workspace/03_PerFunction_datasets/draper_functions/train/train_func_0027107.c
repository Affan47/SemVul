GetBestHypothesis() const
{
  const ChartHypothesis *ret = NULL;
  float bestScore = -std::numeric_limits<float>::infinity();

  MapType::const_iterator iter;
  for (iter = m_hypoColl.begin(); iter != m_hypoColl.end(); ++iter) {
    const HypoList &sortedList = iter->second.GetSortedHypotheses();
    CHECK(sortedList.size() > 0);

    const ChartHypothesis *hypo = sortedList[0];
    if (hypo->GetTotalScore() > bestScore) {
      bestScore = hypo->GetTotalScore();
      ret = hypo;
    };
  }

  return ret;
}
