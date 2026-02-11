ElementWiseSqrtImpl()
  {
    DBG_ASSERT(initialized_);
    if (homogeneous_) {
      scalar_ = sqrt(scalar_);
    }
    else {
      for (Index i=0; i<Dim(); i++) {
        values_[i] = sqrt(values_[i]);
      }
    }
  }
