AddHypothesesToBitmapContainers()
{
  HypothesisStackCubePruning::const_iterator iter;
  for (iter = m_hypos.begin() ; iter != m_hypos.end() ; ++iter) {
    Hypothesis *h = *iter;
    const WordsBitmap &bitmap = h->GetWordsBitmap();
    BitmapContainer *container = m_bitmapAccessor[bitmap];
    container->AddHypothesis(h);
  }
}
