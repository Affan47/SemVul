inverse(CPosePDF &o)  const
{
	ASSERT_(o.GetRuntimeClass() == CLASS_ID(CPosePDFSOG));
	CPosePDFSOG	*out = static_cast<CPosePDFSOG*>( &o );

	const_iterator	itSrc;
	iterator			itDest;

	out->m_modes.resize(m_modes.size());

	for (itSrc=m_modes.begin(),itDest=out->m_modes.begin();itSrc!=m_modes.end();++itSrc,++itDest)
	{

		(itDest)->mean = -(itSrc)->mean;


		(itDest)->cov = (itSrc)->cov;
	}
}
