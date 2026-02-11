ShiftSTDRSMatrix(SmartPtr<DenseSymMatrix>& V,
                   const MultiVectorMatrix& S,
                   const MultiVectorMatrix& DRS)
  {
    Index ndim = V->Dim();
    DBG_ASSERT(S.NCols()==ndim);

    SmartPtr<DenseSymMatrix> new_V = V->MakeNewDenseSymMatrix();

    Number* Vvalues = V->Values();
    Number* new_Vvalues = new_V->Values();
    for (Index j=0; j<ndim-1; j++) {
      for (Index i=j; i<ndim-1; i++) {
        new_Vvalues[i+j*ndim] = Vvalues[i+1+(j+1)*ndim];
      }
    }

    for (Index j=0; j<ndim; j++) {
      new_Vvalues[ndim-1 + j*ndim] =
        S.GetVector(ndim-1)->Dot(*DRS.GetVector(j));
    }

    V = new_V;
  }
