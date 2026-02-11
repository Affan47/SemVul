plain_distance(const PseudoJet & other) const {
  double dphi = abs(phi() - other.phi());
  if (dphi > pi) {dphi = twopi - dphi;}
  double drap = rap() - other.rap();
  return (dphi*dphi + drap*drap);
}
