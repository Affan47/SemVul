sentenceLevelBackgroundBleu(const std::vector<float>& sent, const std::vector<float>& bg)
{

  std::vector<float> stats;
  CHECK(sent.size()==bg.size());
  CHECK(sent.size()==kBleuNgramOrder*2+1);
  for(size_t i=0;i<sent.size();i++)
    stats.push_back(sent[i]+bg[i]);


  float logbleu = 0.0;
  for (int j = 0; j < kBleuNgramOrder; j++) {
    logbleu += log(stats[2 * j]) - log(stats[2 * j + 1]);
  }
  logbleu /= kBleuNgramOrder;
  const float brevity = 1.0 - stats[(kBleuNgramOrder * 2)] / stats[1];

  if (brevity < 0.0) {
    logbleu += brevity;
  }


  return exp(logbleu) * stats[kBleuNgramOrder*2];
}
