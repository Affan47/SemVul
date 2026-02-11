calculateInitialInitialScales(const ShowerPPair &ppair) {


  Lorentz5Momentum p(ppair.first->momentum()+ppair.second->momentum());
  p.boost(p.findBoostToCM());
  Energy Q = sqrt(p.m2());
  if(_initialInitialConditions==1) {
    return pair<Energy,Energy>(sqrt(2.0)*Q,sqrt(0.5)*Q);
  } else if(_initialInitialConditions==2) {
    return pair<Energy,Energy>(sqrt(0.5)*Q,sqrt(2.0)*Q);
  } else {
    return pair<Energy,Energy>(Q,Q);
  }
}
