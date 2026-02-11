readFromStream(mrpt::utils::CStream &in, int version)
{
	switch(version)
	{
	case 1:
		{
			uint32_t	i,n;
			clear();
			in >> n;
			m_posesObsPairs.resize(n);
			for (i=0;i<n;i++)
				in >> m_posesObsPairs[i].first >> m_posesObsPairs[i].second;
		} break;
	case 0:
		{

			uint32_t	i,n;
			clear();
			in >> n;
			m_posesObsPairs.resize(n);
			for (i=0;i<n;i++)
			{
				CPosePDFPtr aux2Dpose;
				in >> aux2Dpose >> m_posesObsPairs[i].second;
				m_posesObsPairs[i].first = CPose3DPDFPtr( CPose3DPDF::createFrom2D( *aux2Dpose ) );
			}
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};
}
