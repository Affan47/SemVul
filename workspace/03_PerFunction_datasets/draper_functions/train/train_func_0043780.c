colourCorrelatedME2(const pair<size_t,size_t>& ij,
					const cPDVector& sub,
					const matrix<Complex>& amp) const {

  const symmetric_matrix<double,upper>& cij = correlator(sub,ij);

  double tr = 0;

  size_t n = amp.size1();

  for ( size_t i = 0; i < n; ++i ) {
    tr += real(inner_prod(row(cij,i),column(amp,i)));
  }

  return tr;

}
