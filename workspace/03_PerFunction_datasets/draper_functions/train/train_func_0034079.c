dT_times_barH_times_d()
  {
    DBG_START_METH("IpoptCalculatedQuantities::dT_times_barH_times_d()",
                   dbg_verbosity);
    Number result;
    SmartPtr<const Vector> d_x = CGPenData().delta_cgfast()->x();
    SmartPtr<const Vector> d_s = CGPenData().delta_cgfast()->s();
    SmartPtr<const Vector> y_c = ip_data_->curr()->y_c();
    SmartPtr<const Vector> y_d = ip_data_->curr()->y_d();
    SmartPtr<const Vector> dy_c = CGPenData().delta_cgfast()->y_c();
    SmartPtr<const Vector> dy_d = CGPenData().delta_cgfast()->y_d();
    SmartPtr<const Vector> c = ip_cq_->curr_c();
    SmartPtr<const Vector> d_minus_s = ip_cq_->curr_d_minus_s();
    Number deriv_barrier_dx = ip_cq_->curr_grad_barrier_obj_x()->Dot(*d_x);
    Number deriv_barrier_dx_ds = deriv_barrier_dx + ip_cq_->curr_grad_barrier_obj_s()->Dot(*d_s);
    Number penalty = CGPenData().curr_penalty();
    result = -y_c->Dot(*dy_c);
    result -= y_d->Dot(*dy_d);
    result *= curr_cg_pert_fact();
    result -= deriv_barrier_dx_ds;
    result += c->Dot(*y_c);
    result += d_minus_s->Dot(*y_d);
    result -= c->Dot(*dy_c);
    result -= d_minus_s->Dot(*dy_d);
    result += penalty*ip_cq_->curr_primal_infeasibility(NORM_2);

    return result;
  }
