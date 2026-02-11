MultiSolve(bool new_matrix,
      const Index* ia, const Index* ja, Index nrhs, double* rhs_vals,
      bool check_NegEVals, Index numberOfNegEVals)
  {
    struct ma77_info info;

    if (new_matrix || pivtol_changed_)
    {
      for(int i=0; i<ndim_; i++) {
         ma77_input_reals(i+1, ia[i+1]-ia[i], &(val_[ia[i]-1]), &keep_,
            &control_, &info);
         if (info.flag < 0) return SYMSOLVER_FATAL_ERROR;
      }

      if (HaveIpData()) {
        IpData().TimingStats().LinearSystemFactorization().Start();
      }

      ma77_factor_solve(0, &keep_, &control_, &info, NULL,
                        nrhs, ndim_, rhs_vals);
      if (HaveIpData()) {
        IpData().TimingStats().LinearSystemFactorization().End();
      }
      if (info.flag==4 || info.flag==-11) return SYMSOLVER_SINGULAR;
      if (info.flag<0) return SYMSOLVER_FATAL_ERROR;
      if (check_NegEVals && info.num_neg!=numberOfNegEVals)
        return SYMSOLVER_WRONG_INERTIA;

      numneg_ = info.num_neg;
      pivtol_changed_ = false;
    }
    else {
      if (HaveIpData()) {
        IpData().TimingStats().LinearSystemBackSolve().Start();
      }
      ma77_solve(0, nrhs, ndim_, rhs_vals, &keep_, &control_, &info, NULL);
      if (HaveIpData()) {
        IpData().TimingStats().LinearSystemBackSolve().End();
      }
    }

    return SYMSOLVER_SUCCESS;
  }
