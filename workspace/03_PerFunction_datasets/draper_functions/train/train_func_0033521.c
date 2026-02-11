Expand(const TranslationOption& topt, Scores& scores) const
{

  HierarchicalReorderingBackwardState* nextState = new HierarchicalReorderingBackwardState(this, topt, m_reoStack);
  ReorderingType reoType;
  const LexicalReorderingConfiguration::ModelType modelType = m_configuration.GetModelType();

  int reoDistance = nextState->m_reoStack.ShiftReduce(topt.GetSourceWordsRange());

  if (modelType == LexicalReorderingConfiguration::MSD) {
    reoType = GetOrientationTypeMSD(reoDistance);
  } else if (modelType == LexicalReorderingConfiguration::MSLR) {
    reoType = GetOrientationTypeMSLR(reoDistance);
  } else if (modelType == LexicalReorderingConfiguration::LeftRight) {
    reoType = GetOrientationTypeLeftRight(reoDistance);
  } else {
    reoType = GetOrientationTypeMonotonic(reoDistance);
  }

  CopyScores(scores, topt, reoType);
  return nextState;
}
