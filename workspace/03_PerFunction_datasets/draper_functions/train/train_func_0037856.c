IsAcceptableToPiecewisePenalty(Number alpha_primal_test)
  {
    DBG_START_METH("CGPenaltyLSAcceptor::IsAcceptableToPiecewisePenalty",
                   dbg_verbosity);


    bool accept = false;
    Number infeasibility = IpCq().curr_primal_infeasibility(NORM_MAX);
    SmartPtr<const Vector> dx = IpData().delta()->x();
    SmartPtr<const Vector> ds = IpData().delta()->s();
    Number curr_barr = IpCq().curr_barrier_obj();
    Number trial_barr = IpCq().trial_barrier_obj();
    Number nrm_dx_ds = pow(dx->Nrm2(),2.) + pow(ds->Nrm2(),2.);
    if (infeasibility < theta_min_) {
      Number biggest_barr = PiecewisePenalty_.BiggestBarr();
      accept = Compare_le(trial_barr-biggest_barr, -alpha_primal_test*
                          piecewisepenalty_gamma_obj_*nrm_dx_ds, curr_barr);
      if (!accept) {
        return false;
      }
    }
    Number Fzconst, Fzlin;
    Fzconst = IpCq().trial_barrier_obj() + alpha_primal_test *
              piecewisepenalty_gamma_obj_ * nrm_dx_ds;
    Fzlin = IpCq().trial_constraint_violation() + alpha_primal_test *
            piecewisepenalty_gamma_infeasi_ * IpCq().curr_constraint_violation();
    accept  = PiecewisePenalty_.Acceptable(Fzconst, Fzlin);
    return accept;
  }
