colourCorrelatedInterference(const pair<size_t,size_t>& ij,
						  const cPDVector& sub,
						  const CVector& left,
						  const CVector& right) const {

  const symmetric_matrix<double,upper>& cij = correlator(sub,ij);
  return inner_prod(conj(left),prod(cij,right));

}
