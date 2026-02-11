GetContigSeqLength( const uint32 i ) const
{
	if( m_contig && (i == 0 || i == ALL_CONTIGS))
		return m_contig->GetSeqLength();
	return GNSEQI_ERROR;
}
