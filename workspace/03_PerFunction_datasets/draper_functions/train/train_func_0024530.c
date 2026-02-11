operator()(const DepthMBBPair &LHS, const DepthMBBPair &RHS) const {

      if (LHS.first != RHS.first)
        return LHS.first > RHS.first;


      unsigned cl = LHS.second->pred_size() + LHS.second->succ_size();
      unsigned cr = RHS.second->pred_size() + RHS.second->succ_size();
      if (cl != cr)
        return cl > cr;


      return LHS.second->getNumber() < RHS.second->getNumber();
    }
