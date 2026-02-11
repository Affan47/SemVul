SpecialAddForLMSR1(const DenseVector& D,
                                          const DenseGenMatrix& L)
  {
    const Index dim = Dim();
    DBG_ASSERT(initialized_);
    DBG_ASSERT(dim==D.Dim());
    DBG_ASSERT(dim==L.NRows());
    DBG_ASSERT(dim==L.NCols());


    const Number* Dvalues = D.Values();
    for (Index i=0; i<dim; i++) {
      values_[i+i*dim] += Dvalues[i];
    }


    const Number* Lvalues = L.Values();
    for (Index j=0; j<dim; j++) {
      for (Index i=j+1; i<dim; i++) {
        values_[i+j*dim] += Lvalues[i+j*dim];
      }
    }
    ObjectChanged();
  }
