DelSource( CUpDownClient* client )
{
	if (m_SrcList.erase(CCLIENTREF(client, wxEmptyString))) {

		if (client && client->IsAdunanzA() && m_AduSrcList_size) m_AduSrcList_size--;

		theStats::RemoveSourceOrigin(client->GetSourceFrom());
		theStats::RemoveFoundSource();
		return true;
	} else {
		return false;
	}
}
