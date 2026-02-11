MultVectorImpl(Number alpha, const Vector &x,
                                         Number beta, Vector &y) const
  {
    if (!matrices_valid_) {
      matrices_valid_ = MatricesValid();
    }
    DBG_ASSERT(matrices_valid_);


    const CompoundVector* comp_x = static_cast<const CompoundVector*>(&x);
    DBG_ASSERT(dynamic_cast<const CompoundVector*>(&x));
    CompoundVector* comp_y = static_cast<CompoundVector*>(&y);
    DBG_ASSERT(dynamic_cast<CompoundVector*>(&y));


    if (comp_x) {
      DBG_ASSERT(NComps_Dim()==comp_x->NComps());
    }
    else {
      DBG_ASSERT(NComps_Dim() == 1);
    }
    if (comp_y) {
      DBG_ASSERT(NComps_Dim()==comp_y->NComps());
    }
    else {
      DBG_ASSERT(NComps_Dim() == 1);
    }


    if ( beta!=0.0 ) {
      y.Scal(beta);
    }
    else {
      y.Set(0.0);
    }

    for (Index irow=0; irow<NComps_Dim(); irow++) {
      SmartPtr<Vector> y_i;
      if (comp_y) {
        y_i = comp_y->GetCompNonConst(irow);
      }
      else {
        y_i = &y;
      }
      DBG_ASSERT(IsValid(y_i));

      for (Index jcol=0; jcol<=irow; jcol++) {
        SmartPtr<const Vector> x_j;
        if (comp_x) {
          x_j = comp_x->GetComp(irow);
        }
        else {
          x_j = &x;
        }
        DBG_ASSERT(IsValid(x_j));

        if (ConstComp(irow,jcol)) {
          ConstComp(irow,jcol)->MultVector(alpha, *comp_x->GetComp(jcol),
                                           1., *comp_y->GetCompNonConst(irow));
        }
      }

      for (Index jcol = irow+1; jcol < NComps_Dim(); jcol++) {
        if (ConstComp(jcol,irow)) {
          ConstComp(jcol,irow)->TransMultVector(alpha, *comp_x->GetComp(jcol),
                                                1., *comp_y->GetCompNonConst(irow));
        }
      }
    }
  }
