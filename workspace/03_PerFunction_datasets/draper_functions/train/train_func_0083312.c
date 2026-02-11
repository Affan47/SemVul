unscaled_curr_nlp_error()
  {
    DBG_START_METH("IpoptCalculatedQuantities::unscaled_curr_nlp_error()",
                   dbg_verbosity);
    DBG_ASSERT(initialize_called_);
    Number result;

    SmartPtr<const Vector> x = ip_data_->curr()->x();
    SmartPtr<const Vector> s = ip_data_->curr()->s();
    SmartPtr<const Vector> y_c = ip_data_->curr()->y_c();
    SmartPtr<const Vector> y_d = ip_data_->curr()->y_d();
    SmartPtr<const Vector> z_L = ip_data_->curr()->z_L();
    SmartPtr<const Vector> z_U = ip_data_->curr()->z_U();
    SmartPtr<const Vector> v_L = ip_data_->curr()->v_L();
    SmartPtr<const Vector> v_U = ip_data_->curr()->v_U();

    std::vector<const TaggedObject*> tdeps(8);
    tdeps[0] = GetRawPtr(x);
    tdeps[1] = GetRawPtr(s);
    tdeps[2] = GetRawPtr(y_c);
    tdeps[3] = GetRawPtr(y_d);
    tdeps[4] = GetRawPtr(z_L);
    tdeps[5] = GetRawPtr(z_U);
    tdeps[6] = GetRawPtr(v_L);
    tdeps[7] = GetRawPtr(v_U);

    if (!unscaled_curr_nlp_error_cache_.GetCachedResult(result, tdeps)) {


      result = unscaled_curr_dual_infeasibility(NORM_MAX);

      result = Max(result, unscaled_curr_nlp_constraint_violation(NORM_MAX));

      DBG_PRINT((1, "curr_complementarity(mu_target_, NORM_MAX) = %8.2e\n",
                 curr_complementarity(mu_target_, NORM_MAX)));
      result = Max(result, unscaled_curr_complementarity(mu_target_, NORM_MAX));

      unscaled_curr_nlp_error_cache_.AddCachedResult(result, tdeps);
    }

    return result;
  }
