get_bounds_info(Index n, Number* x_l, Number* x_u,
                               Index m, Number* g_l, Number* g_u)
  {
    Number* g_l_orig = new Number[m_orig_];
    Number* g_u_orig = new Number[m_orig_];

    bool retval = tnlp_->get_bounds_info(n, x_l, x_u,
                                         m_orig_, g_l_orig, g_u_orig);

    if (retval) {

      if (n_x_fix_>0 || n_xL_skip_>0 || n_xU_skip_>0) {
        const Number huge = std::numeric_limits<Number>::max();


        Number* x_start = NULL;
        if (n_x_fix_>0) {
          x_start = new Number[n];
          retval = tnlp_->get_starting_point(n, true, x_start, false, NULL,
                                             NULL, m_orig_, false, NULL);
          if (!retval) return false;
        }

        Index count_xL = 0;
        Index count_xU = 0;
        Index count_x = 0;
        for (Index i=0; i<n; i++) {
          if (index_xL_skip_[count_xL]==i) {
            x_l[i] = -huge;
            count_xL++;
          }
          if (index_xU_skip_[count_xU]==i) {
            x_u[i] = huge;
            count_xU++;
          }
          if (index_x_fix_[count_x]==i) {
            x_l[i] = x_start[i];
            x_u[i] = x_start[i];
            count_x++;
          }
        }
        delete [] x_start;
      }

      for (Index i=0; i<m_orig_; i++) {
        Index& new_index = g_keep_map_[i];
        if (new_index >= 0) {
          g_l[new_index] = g_l_orig[i];
          g_u[new_index] = g_u_orig[i];
        }
      }
    }

    delete [] g_l_orig;
    delete [] g_u_orig;

    return retval;
  }
