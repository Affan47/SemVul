operator== ( const HepGenMatrix& o) const {
  if(o.num_row()!=num_row() || o.num_col()!=num_col()) return false;
  for (int k1=1; k1<=num_row(); k1++)
    for (int k2=1; k2<=num_col(); k2++)
      if(o(k1,k2) != (*this)(k1,k2)) return false;
  return true;
}
