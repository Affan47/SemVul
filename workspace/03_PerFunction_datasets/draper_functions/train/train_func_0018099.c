HasValidNumbersImpl() const
  {
    DBG_ASSERT(initialized_);
    Number sum = 0.;
    const Index dim = Dim();
    for (Index j=0; j<dim; j++) {
      sum += values_[j + j*dim];
      for (Index i=j+1; i<dim; i++) {
        sum += values_[i + j*dim];
      }
    }
    return IsFiniteNumber(sum);
  }
