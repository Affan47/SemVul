partial(unsigned int index) const {
  const AbsFunction & fPrime = _arg1->partial(index) - _arg2->partial(index);
  return Derivative(&fPrime);
}


}
