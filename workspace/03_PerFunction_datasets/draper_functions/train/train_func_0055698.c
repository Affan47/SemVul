SymbolicFactorization(const Index*  airn,
      const Index*  ajcn)
  {
    DBG_START_METH("Ma57TSolverInterface::SymbolicFactorization",dbg_verbosity);

    if (HaveIpData()) {
      IpData().TimingStats().LinearSystemSymbolicFactorization().Start();
    }

    ma57int n  = dim_;
    ma57int ne = nonzeros_;

    wd_lkeep_ = 5*n + ne + (n > ne ? n : ne) + 42;

    wd_cntl_[1-1]  = pivtol_;

    wd_iwork_ = new ma57int[5*n];
    wd_keep_  = new ma57int[wd_lkeep_];

    for (int k=0; k<wd_lkeep_; k++) {
      wd_keep_[k] = 0;
    }


    ma57int* airn_ma57int;
    ma57int* ajcn_ma57int;
    if (sizeof(ma57int) != sizeof(Index)) {
      airn_ma57int = new ma57int[ne];
      ajcn_ma57int = new ma57int[ne];
      for (int k = 0; k < ne; ++k) {
        airn_ma57int[k] = (ma57int) airn[k];
        ajcn_ma57int[k] = (ma57int) ajcn[k];
      }
    } else {
       airn_ma57int = (ma57int*)(void*)const_cast<Index*>(airn);
       ajcn_ma57int = (ma57int*)(void*)const_cast<Index*>(ajcn);
    }

    F77_FUNC (ma57ad, MA57AD)
    (&n, &ne, airn_ma57int, ajcn_ma57int, &wd_lkeep_, wd_keep_, wd_iwork_,
     wd_icntl_, wd_info_, wd_rinfo_);


    if (sizeof(ma57int) != sizeof(Index)) {
      delete [] airn_ma57int;
      delete [] ajcn_ma57int;
    }

    if (wd_info_[0] < 0) {
      Jnlst().Printf(J_ERROR, J_LINEAR_ALGEBRA,
                     "*** Error from MA57AD *** INFO(0) = %d\n", wd_info_[0]);
    }

    wd_lfact_  = (ma57int)((Number)wd_info_[8] * ma57_pre_alloc_);
    wd_lifact_ = (ma57int)((Number)wd_info_[9] * ma57_pre_alloc_);


    delete [] wd_fact_;
    wd_fact_ = NULL;
    delete [] wd_ifact_;
    wd_ifact_ = NULL;

    wd_fact_  = new double[wd_lfact_];
    wd_ifact_ = new ma57int[wd_lifact_];

    Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                   "Suggested lfact  (*%e):  %d\n", ma57_pre_alloc_, wd_lfact_);
    Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                   "Suggested lifact (*%e):  %d\n", ma57_pre_alloc_, wd_lifact_);

    if (HaveIpData()) {
      IpData().TimingStats().LinearSystemSymbolicFactorization().End();
    }
    return SYMSOLVER_SUCCESS;
  }
