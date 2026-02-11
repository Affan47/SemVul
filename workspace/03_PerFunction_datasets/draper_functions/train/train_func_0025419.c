trial_f()
  {
    DBG_START_METH("IpoptCalculatedQuantities::trial_f()",
                   dbg_verbosity);
    Number result;
    SmartPtr<const Vector> x = ip_data_->trial()->x();
    DBG_PRINT_VECTOR(2,"trial_x",*x);
    DBG_PRINT((1, "trial_x tag = (%p,%d)\n", x->GetTag().first, x->GetTag().second));

    bool objective_depends_on_mu = ip_nlp_->objective_depends_on_mu();
    std::vector<const TaggedObject*> tdeps(1);
    tdeps[0] = GetRawPtr(x);
    std::vector<Number> sdeps(1);
    if (objective_depends_on_mu) {
      sdeps[0] = ip_data_->curr_mu();
    }
    else {
      sdeps[0] = -1.;
    }

    if (!trial_f_cache_.GetCachedResult(result, tdeps, sdeps)) {
      if (!curr_f_cache_.GetCachedResult(result, tdeps, sdeps)) {
        DBG_PRINT((2,"evaluate trial f\n"));
        if (objective_depends_on_mu) {
          result = ip_nlp_->f(*x, ip_data_->curr_mu());
        }
        else {
          result = ip_nlp_->f(*x);
        }
      }
      trial_f_cache_.AddCachedResult(result, tdeps, sdeps);
    }
    DBG_PRINT((1,"result (trial_f) = %e\n", result));
    return result;
  }
