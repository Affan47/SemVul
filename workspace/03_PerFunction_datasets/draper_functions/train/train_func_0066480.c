internal_eval_jac_g(bool new_x)
  {
    if (x_tag_for_jac_g_ == x_tag_for_iterates_) {

      return true;
    }

    x_tag_for_jac_g_ = x_tag_for_iterates_;

    bool retval;
    if (jacobian_approximation_ == JAC_EXACT) {
      retval = tnlp_->eval_jac_g(n_full_x_, full_x_, new_x, n_full_g_,
                                 nz_full_jac_g_, NULL, NULL, jac_g_);
    }
    else {

      retval = internal_eval_g(new_x);
      if (retval) {
        Number* full_g_pert = new Number[n_full_g_];
        Number* full_x_pert = new Number[n_full_x_];
        IpBlasDcopy(n_full_x_, full_x_, 1, full_x_pert, 1);

        for (Index ivar = 0; ivar<n_full_x_; ivar++) {
          if (findiff_x_l_[ivar] < findiff_x_u_[ivar]) {
            const Number xorig = full_x_pert[ivar];
            Number this_perturbation =
              findiff_perturbation_*Max(1., fabs(full_x_[ivar]));
            full_x_pert[ivar] += this_perturbation;
            if (full_x_pert[ivar] > findiff_x_u_[ivar]) {
              full_x_pert[ivar] = xorig - this_perturbation;
            }
            retval = tnlp_->eval_g(n_full_x_, full_x_pert, true, n_full_g_,
                                   full_g_pert);
            if (!retval) break;
            for (Index i=findiff_jac_ia_[ivar]; i<findiff_jac_ia_[ivar+1]; i++) {
              const Index& icon = findiff_jac_ja_[i];
              const Index& ipos = findiff_jac_postriplet_[i];
              jac_g_[ipos] =
                (full_g_pert[icon]-full_g_[icon])/this_perturbation;
            }
            full_x_pert[ivar] = xorig;
          }
        }
        delete [] full_g_pert;
        delete [] full_x_pert;
      }
    }

    if (!retval) {
      x_tag_for_jac_g_ = TaggedObject::Tag();
    }

    return retval;
  }
