curr_primal_frac_to_the_bound(Number tau)
  {
    DBG_START_METH("IpoptCalculatedQuantities::curr_primal_frac_to_the_bound()",
                   dbg_verbosity);
    return primal_frac_to_the_bound(tau, *ip_data_->delta()->x(),
                                    *ip_data_->delta()->s());
  }
