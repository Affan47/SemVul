isLargest() const {


  return isFiniteNonZero() && exponent == semantics->maxExponent
    && isSignificandAllOnes();
}
