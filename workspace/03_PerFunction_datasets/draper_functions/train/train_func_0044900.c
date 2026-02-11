clusteredState(int nSteps) {


  Event outState = state;

  if (mother && nSteps > 0)
    outState = mother->clusteredState(nSteps - 1);

  return outState;

}
