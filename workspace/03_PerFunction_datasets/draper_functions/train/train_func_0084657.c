_split_once(const PseudoJet & jet_to_split,
                                           const PseudoJet & reference_jet) const{
  PseudoJet this_jet = jet_to_split;
  PseudoJet p1, p2;
  vector<PseudoJet> result_local;
  while (this_jet.has_parents(p1, p2)) {
    if (p2.perp2() > p1.perp2()) std::swap(p1,p2);
    if (p1.perp() < _delta_p * reference_jet.perp()) break;
    if ( (abs(p2.rap()-p1.rap()) + abs(p2.delta_phi_to(p1))) < _delta_r) break;
    if (p2.perp() < _delta_p * reference_jet.perp()) {
      this_jet = p1;
      continue;
    }

    result_local.push_back(p1);
    result_local.push_back(p2);
    break;
  }
  return result_local;
}
