OutputPasses(GrcManager * pcman, GrcBinaryStream * pbstrm, long lTableStart,
	std::vector<int> & vnOffsets)
{
	for (size_t ipass = 0; ipass < m_vppass.size(); ++ipass)
	{
		if (m_vppass[ipass]->HasRules())
		{
			vnOffsets.push_back(pbstrm->Position() - lTableStart);
			m_vppass[ipass]->OutputPass(pcman, pbstrm, lTableStart);
		}
	}
}
