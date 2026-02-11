countBodySamples(const FunctionSamples *Samples) const {
  unsigned Count = Samples->getBodySamples().size();
  for (const auto &I : Samples->getCallsiteSamples())
    Count += countBodySamples(&I.second);
  return Count;
}
