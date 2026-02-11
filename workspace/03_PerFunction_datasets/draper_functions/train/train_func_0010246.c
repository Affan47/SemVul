prepareStats(size_t sid, const string& text, ScoreStats& entry)
{
  vector<ScoreStatsType> stats;

  const string& sentence = preprocessSentence(text);
  str_sentence_t splitCandSentence;
  splitSentence(sentence, splitCandSentence);

  sentence_t encodedCandSentence;
  encodeSentence(splitCandSentence, encodedCandSentence);

  if (m_ref_sentences.size() == 1) {
    stats = m_ovr->prepareStats(encodedCandSentence, m_ref_sentences[0][sid]);
  } else {
    float max = -1.0f;
    for (size_t rid = 0; rid < m_ref_sentences.size(); ++rid) {
      const vector<ScoreStatsType>& tmp = m_ovr->prepareStats(encodedCandSentence, m_ref_sentences[rid][sid]);
      if (m_ovr->calculateScore(tmp) > max) {
        stats = tmp;
      }
    }
  }
  entry.set(stats);
}
