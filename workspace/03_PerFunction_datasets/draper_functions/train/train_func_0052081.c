operator<< (std::ostream& o, const extLong& x) {
  if (x.flag == 1)
    o << " infty ";
  else if (x.flag == - 1)
    o << " tiny ";
  else if (x.flag == 2)
    o << " NaN ";
  else
    o << x.val;
  return o;
}
