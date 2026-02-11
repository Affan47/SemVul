getDomainOfSentence( int sentenceId ) const {
  for(size_t i=0; i<spec.size(); i++) {
    if (sentenceId <= spec[i].first) {
      return spec[i].second;
    }
  }
  return "undefined";
}
