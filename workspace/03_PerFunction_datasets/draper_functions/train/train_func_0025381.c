is_pure_ghost(const PseudoJet & ) const{
  for (unsigned i = 0; i < _pieces.size(); i++)
    if (! _pieces[i].is_pure_ghost()) return false;

  return true;
}
