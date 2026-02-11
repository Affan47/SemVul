Contains( const gnSeqC* seq, const gnSeqC* seq2, const uint32 len, boolean case_sensitive ) const{
	for( uint32 i=0; i < len ; ++i )
		if(!Contains(seq[i], seq2[i], case_sensitive))
			return false;
	return true;
}
