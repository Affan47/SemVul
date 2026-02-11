Initialize(const Journalist& jnlst,
                             const OptionsList& options,
                             const std::string& prefix)
  {
#if 0


    if (prefix=="resto.") {


      if (!options.GetNumericValue("resto.tol", tol_, "")) {
        options.GetNumericValue("tol", tol_, prefix);
        tol_ *= 1e-2;
      }
    }
    else {
      options.GetNumericValue("tol", tol_, prefix);
    }
#else
    options.GetNumericValue("tol", tol_, prefix);
#endif

    iter_count_ = 0;
    curr_mu_ = -1.;
    mu_initialized_ = false;
    curr_tau_ = -1.;
    tau_initialized_ = false;
    have_prototypes_ = false;
    have_deltas_ = false;
    have_affine_deltas_ = false;

    free_mu_mode_ = false;
    tiny_step_flag_ = false;

    info_ls_count_ = 0;
    ResetInfo();
    info_last_output_ = -1.;
    info_iters_since_header_ = 1000;

    initialize_called_ = true;

    if (cpu_time_start_==-1.) {
      cpu_time_start_ = CpuTime();
    }

    bool retval = true;

    if (IsValid(add_data_)) {
      retval = add_data_->Initialize(jnlst, options, prefix);
    }

    return retval;
  }
