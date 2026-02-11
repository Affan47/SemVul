prepareStatsVector(size_t sid, const string& text, vector<int>& stats)
{
  sent_t cand;
  TokenizeAndEncode(text, cand);

  float max = -2;
  vector<int> tmp;
  for (size_t rid = 0; rid < m_ref_sentences.size(); ++rid) {
    const sent_t& ref = m_ref_sentences[rid][sid];
    tmp.clear();
    computeCD(cand, ref, tmp);
    if (calculateScore(tmp) > max) {
      stats = tmp;
    }
  }
}
