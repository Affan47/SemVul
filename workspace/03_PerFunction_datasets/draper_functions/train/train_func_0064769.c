insert( const CPosePDF *in_posePDF, const CSensoryFrame &in_SF )
{
	MRPT_START

	TPosePDFSensFramePair	pair;

	pair.second  = CSensoryFramePtr( new CSensoryFrame(in_SF) );
	pair.first	 = CPose3DPDFPtr( static_cast<CPose3DPDF*>(in_posePDF->duplicate()) );

	m_posesObsPairs.push_back( pair );

	MRPT_END
}
