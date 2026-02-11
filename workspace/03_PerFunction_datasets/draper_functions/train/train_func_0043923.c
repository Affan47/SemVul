hook(EncaAnalyserState *analyser)
{
  const size_t* order = analyser->order;
  double* rating_first = &analyser->ratings[order[0]];
  double* rating_second = &analyser->ratings[order[1]];

  if (*rating_second < 0) {
    *rating_second = 0.;

    if (*rating_first < 0)
      *rating_first = 0.;
    else
      *rating_first = 1.;

    return 1;
  }

  return 0;
}
