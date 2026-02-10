GetIndex(const_iterator record) const
{
	const_iterator i = begin();
	for( int index = 0; i != end(); ++i, index++ ) {
		if( i == record )
			return index;
	}
	return -1;
}
