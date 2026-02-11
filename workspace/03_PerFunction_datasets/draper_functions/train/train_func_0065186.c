_check_explicit_ghosts(const vector<PseudoJet> &all_pieces) const{
  for (vector<PseudoJet>::const_iterator it=all_pieces.begin(); it!=all_pieces.end(); it++)
    if (! it->validated_csab()->has_explicit_ghosts()) return false;
  return true;
}
