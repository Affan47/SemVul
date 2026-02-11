DispatchBuild(util::FilePiece &f, const std::vector<uint64_t> &counts, const Config &config, const ProbingVocabulary &vocab, PositiveProbWarn &warn) {
  switch (config.rest_function) {
    case Config::REST_MAX:
      {
        MaxRestBuild build;
        ApplyBuild(f, counts, vocab, warn, build);
      }
      break;
    case Config::REST_LOWER:
      {
        LowerRestBuild<ProbingModel> build(config, counts.size(), vocab);
        ApplyBuild(f, counts, vocab, warn, build);
      }
      break;
  }
}
