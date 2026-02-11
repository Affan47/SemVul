partial(unsigned int index) const {
  Sigma fPrime;
  for (size_t i=0;i<_fcn.size();i++) {
    fPrime.accumulate(_fcn[i]->partial(index));
  }
  return Derivative(&fPrime);
}
