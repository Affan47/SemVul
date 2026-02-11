selfMedian()
{
  double maxP = _selfHisto[0];
  int medD = 0;
  for (int i = 1;i<maxHistogramDepth;i++)
    if (_selfHisto[i]>maxP) {
      maxP = _selfHisto[i];
      medD = i;
    }

  return medD;
}
