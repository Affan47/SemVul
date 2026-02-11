autoReduce(bool &success, PolynomialSet const &idealGenerators)
  {
    success=true;
    PolynomialSet ret=idealGenerators;
    autoReduce_(&ret,LexicographicTermOrder());
    return ret;
  }
