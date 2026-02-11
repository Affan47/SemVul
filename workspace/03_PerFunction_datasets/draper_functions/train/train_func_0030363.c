process_target_mu(Number factor,
      const Vector& curr_vars,
      const Vector& curr_slacks,
      const Vector& curr_mults,
      const Matrix& P,
      SmartPtr<const Vector>& ret_vars,
      SmartPtr<const Vector>& ret_mults)
  {
    SmartPtr<Vector> new_slacks = curr_slacks.MakeNewCopy();
    SmartPtr<Vector> new_mults = curr_mults.MakeNewCopy();
    adapt_to_target_mu(*new_slacks, *new_mults, warm_start_target_mu_);
    new_slacks->Axpy(-1, curr_slacks);
    SmartPtr<Vector> new_vars = curr_vars.MakeNew();
    new_vars->Copy(curr_vars);
    P.MultVector(factor, *new_slacks, 1., *new_vars);

    ret_vars = ConstPtr(new_vars);
    ret_mults = ConstPtr(new_mults);
  }
