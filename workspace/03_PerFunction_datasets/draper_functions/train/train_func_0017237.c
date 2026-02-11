Acceptable(Number Fzconst, Number Fzlin)
  {
    DBG_START_METH("PiebcewisePenalty::Acceptable", dbg_verbosity);
    DBG_ASSERT(!IsPiecewisePenaltyListEmpty());
    bool acceptable = false;
    std::vector<PiecewisePenEntry>::iterator iter;


    Index size = (Index)PiecewisePenalty_list_.size();
    if (size >= max_piece_number_) {
      Number trial_inf = Fzlin;
      Number trial_barrier = Fzconst;

      iter = PiecewisePenalty_list_.begin();
      Number value = iter->barrier_obj + iter->pen_r * iter->infeasi
                     - trial_barrier - iter->pen_r * trial_inf;
      if (value >= 0.) {
        iter++;
        value = iter->barrier_obj + iter->pen_r * iter->infeasi
                - trial_barrier - iter->pen_r * trial_inf;
        if (value <= 0.) {
          return false;
        }
      }

      iter = PiecewisePenalty_list_.end();
      iter--;
      value = iter->barrier_obj + iter->pen_r * iter->infeasi
              - trial_barrier - iter->pen_r * trial_inf;
      if (value <= 0. && trial_inf <= iter->infeasi) {
        return false;
      }

      if (value >= 0. && trial_inf >= iter->infeasi) {
        iter-=1;
        value = iter->barrier_obj + iter->pen_r * iter->infeasi
                - trial_barrier - iter->pen_r * trial_inf;
        if (value <= 0.) {
          return false;
        }
      }

      Number value_left, value_mid, value_right;
      for (iter = PiecewisePenalty_list_.begin() +1; iter != PiecewisePenalty_list_.end();
           iter++) {
        value_mid = iter->barrier_obj + iter->pen_r * iter->infeasi
                    - trial_barrier - iter->pen_r * trial_inf;
        iter++;
        value_right = iter->barrier_obj + iter->pen_r * iter->infeasi
                      - trial_barrier - iter->pen_r * trial_inf;
        iter-=2;
        value_left = iter->barrier_obj + iter->pen_r * iter->infeasi
                     - trial_barrier - iter->pen_r * trial_inf;
        iter++;
        if (value_left <= 0. && value_mid >= 0. && value_right <= 0.) {
          return false;
        }
      }
    }

    Number Fz;
    for (iter = PiecewisePenalty_list_.begin(); iter != PiecewisePenalty_list_.end();
         iter++) {
      Fz = Fzconst + iter->pen_r * (Fzlin - iter->infeasi) - iter->barrier_obj ;
      if (Fz < 0.) {
        acceptable = true;
        break;
      }
    }
    iter = PiecewisePenalty_list_.end() -1;
    if (acceptable == false && Fzlin < iter->infeasi) {
      acceptable = true;
    }
    return acceptable;
  }
