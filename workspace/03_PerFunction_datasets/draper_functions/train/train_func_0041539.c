chargeProduct(const compressed_matrix<double>& ti,
				const vector<pair<size_t,size_t> >& tiNonZero,
				const symmetric_matrix<double,upper>& X,
				const compressed_matrix<double>& tj,
				const vector<pair<size_t,size_t> >& tjNonZero,
				symmetric_matrix<double,upper>& result) const {
  for ( size_t i = 0; i < result.size1(); ++i )
    for ( size_t j = i; j < result.size1(); ++j )
      result(i,j) = 0.;
  for ( vector<pair<size_t,size_t> >::const_iterator i = tiNonZero.begin();
	i != tiNonZero.end(); ++i )
    for ( vector<pair<size_t,size_t> >::const_iterator j = tjNonZero.begin();
	  j != tjNonZero.end(); ++j ) {
      if ( j->second < i->second )
	continue;
      result(i->second,j->second) +=
	ti(i->first,i->second)*tj(j->first,j->second)*X(i->first,j->first);
    }
}
