D_x_plus_wr_d(
    const SmartPtr<const Vector>& CD_x0,
    Number factor,
    const Vector& wr_d)
  {
    DBG_START_METH("AugRestoSystemSolver::D_x_plus_wr_d",dbg_verbosity);
    SmartPtr<Vector> retVec;

    std::vector<const TaggedObject*> deps(2);
    deps[0] = &wr_d;
    if (IsValid(CD_x0)) {
      deps[1] = GetRawPtr(CD_x0);
    }
    else {
      deps[1] = NULL;
    }
    std::vector<Number> scalar_deps(1);
    scalar_deps[0] = factor;

    if (!d_x_plus_wr_d_cache_.GetCachedResult(retVec, deps, scalar_deps)) {
      DBG_PRINT((1,"Not found in cache\n"));
      retVec = wr_d.MakeNew();

      Number fact;
      SmartPtr<const Vector> v;
      if (IsValid(CD_x0)) {
        fact = 1.;
        v = CD_x0;
      }
      else {
        fact = 0.;
        v = &wr_d;
      }
      retVec->AddTwoVectors(factor, wr_d, fact, *v, 0.);

      d_x_plus_wr_d_cache_.AddCachedResult(retVec, deps, scalar_deps);
    }
    DBG_PRINT_VECTOR(2, "retVec", *retVec);
    return ConstPtr(retVec);
  }
