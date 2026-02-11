curr_direct_deriv_penalty_function()
  {
    DBG_START_METH("CGPenaltyCq::curr_direct_deriv_penalty_function()",
                   dbg_verbosity);

    Number result;
    SmartPtr<const Vector> x = ip_data_->curr()->x();
    SmartPtr<const Vector> s = ip_data_->curr()->s();
    SmartPtr<const Vector> y_c = ip_data_->curr()->y_c();
    SmartPtr<const Vector> y_d = ip_data_->curr()->y_d();
    SmartPtr<const Vector> dy_c = CGPenData().delta_cgpen()->y_c();
    SmartPtr<const Vector> dy_d = CGPenData().delta_cgpen()->y_d();
    SmartPtr<const Vector> dx = CGPenData().delta_cgpen()->x();
    SmartPtr<const Vector> ds = CGPenData().delta_cgpen()->s();
    std::vector<const TaggedObject*> tdeps(8);
    tdeps[0] = GetRawPtr(x);
    tdeps[1] = GetRawPtr(s);
    tdeps[2] = GetRawPtr(y_c);
    tdeps[3] = GetRawPtr(y_d);
    tdeps[4] = GetRawPtr(dy_c);
    tdeps[5] = GetRawPtr(dy_d);
    tdeps[6] = GetRawPtr(dx);
    tdeps[7] = GetRawPtr(ds);
    Number mu = ip_data_->curr_mu();
    Number penalty = CGPenData().curr_penalty();
    std::vector<Number> sdeps(2);
    sdeps[0] = mu;
    sdeps[1] = penalty;
    if (!curr_direct_deriv_penalty_function_cache_.GetCachedResult(result, tdeps, sdeps)) {
      result = ip_cq_->curr_grad_barrier_obj_x()->Dot(*dx) +
               ip_cq_->curr_grad_barrier_obj_s()->Dot(*ds);
      Number curr_inf = ip_cq_->curr_primal_infeasibility(NORM_2);
      result -= penalty*curr_inf;
      if (curr_inf != 0.) {
        Number fac = penalty*CGPenData().CurrPenaltyPert()/curr_inf;
        SmartPtr<const Vector> c = ip_cq_->curr_c();
        SmartPtr<const Vector> d_minus_s = ip_cq_->curr_d_minus_s();
        Number result1 = c->Dot(*y_c);
        result1 += c->Dot(*dy_c);
        result1 += d_minus_s->Dot(*y_d);
        result1 += d_minus_s->Dot(*dy_d);
        result1 *= fac;
        result += result1;
      }
      curr_direct_deriv_penalty_function_cache_.AddCachedResult(result, tdeps, sdeps);
    }
    return result;
  }
