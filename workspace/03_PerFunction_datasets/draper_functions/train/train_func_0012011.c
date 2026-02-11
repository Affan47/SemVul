poisson(Length b, CrossSection sigma, unsigned int N, Energy2 mu2) const {
  if(sigma > 0*millibarn){
    return pow(OverlapFunction(b, mu2)*sigma, (double)N)/factorial(N)
      *exp(-OverlapFunction(b, mu2)*sigma);
  }else{
    return (N==0) ? 1.0 : 0.0;
  }
}
