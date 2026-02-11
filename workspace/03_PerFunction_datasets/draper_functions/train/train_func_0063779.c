operator()(double inProbability)const{


  return
    ((inProbability
      >
      mThreshold)
     &&
     (mSum>0))
    ? -log(inProbability/mSum)*(inProbability/mSum)
    : 0;
}
