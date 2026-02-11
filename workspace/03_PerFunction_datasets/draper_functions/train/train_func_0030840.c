operator()(double inProbability)const{
  return
    (inProbability>0)
    ? -log(inProbability)*inProbability
    : 0;
}
