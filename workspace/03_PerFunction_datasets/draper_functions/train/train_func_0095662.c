SumImpl() const
  {
    DBG_ASSERT(initialized_);
    Number sum;
    if (homogeneous_) {
      sum = Dim()*scalar_;
    }
    else {
      sum = 0.;
      for (Index i=0; i<Dim(); i++) {
        sum += values_[i];
      }
    }
    return sum;
  }
