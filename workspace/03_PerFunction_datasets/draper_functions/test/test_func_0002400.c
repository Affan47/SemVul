min_ref_val()
  {
    DBG_ASSERT(adaptive_mu_globalization_==KKT_ERROR);
    Number min_ref;
    DBG_ASSERT(refs_vals_.size()>0);
    std::list<Number>::iterator iter = refs_vals_.begin();
    min_ref = *iter;
    iter++;
    while (iter != refs_vals_.end()) {
      min_ref = Min(min_ref, *iter);
      iter++;
    }
    return min_ref;
  }
