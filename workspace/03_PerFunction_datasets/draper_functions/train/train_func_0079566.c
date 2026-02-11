get_starting_point(Index n, bool init_x, Number* x,
                                  bool init_z, Number* z_L, Number* z_U,
                                  Index m, bool init_lambda,
                                  Number* lambda)
  {
    Number* lambda_orig = NULL;
    if (init_lambda) {
      lambda_orig = new Number[m_orig_];
    }

    bool retval = tnlp_->get_starting_point(n, init_x, x, init_z, z_L, z_U,
                                            m_orig_, init_lambda, lambda_orig);

    if (retval && init_lambda) {
      for (Index i=0; i<m_orig_; i++) {
        Index& new_index = g_keep_map_[i];
        if (new_index >= 0) {
          lambda[new_index] = lambda_orig[i];
        }
      }
    }

    delete [] lambda_orig;

    return retval;
  }
