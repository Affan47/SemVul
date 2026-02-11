skewedTransition(Bitext* b, double** transition, double exp){
  int sourceLen = b->getSourceLength();
  int targetLen = b->getTargetLength();

  for (int ii=1; ii<=sourceLen; ii++){
    transition[0][ii] = 1.0/ii;
  }
  for (int i=1; i<=sourceLen; i++){
    for (int ii=1; ii<=sourceLen+1; ii++){
      double denom = 1;
      if (i>ii) denom = i-ii;
      if (ii>i) denom = ii-i;
      transition[i][ii] = 1.0/pow(denom, exp);
    }
  }
  transition[0][sourceLen+1] = 0.0;
}
