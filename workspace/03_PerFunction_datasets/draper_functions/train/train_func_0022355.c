cost(const Space&, const ModEventDelta&) const {
    return PropCost::quadratic(PropCost::HI,bs.size());
  }
