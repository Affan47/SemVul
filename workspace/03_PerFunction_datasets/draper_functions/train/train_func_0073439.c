operator()()const{
  return
    bool((const CAcURL2FTS&)(*this))
    &&
    bool((const CDistanceCalculator&)(*this));
}
