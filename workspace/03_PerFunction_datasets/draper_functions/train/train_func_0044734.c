min( Vector<long> &v )
{
	Vector<long>::Iter i = v;
	long m = *i;
	i++;
	for ( ; i.lte(); i++ ) {
		if ( *i < m )
			m = *i;
	}
	return m;
}
