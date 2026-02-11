saveDistState ( std::ostream & os ) {
  int prec = os.precision(20);
  std::vector<unsigned long> t(2);
  os << distributionName() << "\n";
  os << "Uvec\n";
  if ( getFlag() ) {
    t = DoubConv::dto2longs(getVal());
    os << "nextGauss_st " << getVal() << " " << t[0] << " " << t[1] << "\n";
  } else {
    os << "no_cached_nextGauss_st \n";
  }
  os.precision(prec);
  return os;
}
