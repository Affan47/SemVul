operator() (double xi) const {
  cPDVector::const_iterator d = dataBegin;
  vector<Lorentz5Momentum>::const_iterator p = momentaBegin;
  Energy res = -w;
  for ( ; d != dataEnd; ++d, ++p ) {
    res += sqrt(sqr((**d).mass()) +
		xi*xi*sqr(p->t()));
  }
  return res;
}
