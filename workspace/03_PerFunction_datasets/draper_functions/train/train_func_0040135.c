updateRawData(const CmtRawData& data, const uint16_t index)
{
	if (getDataSize(index) == 0)
		return false;
	if (m_infoList[index].m_rawData == CMT_DATA_ITEM_NOT_AVAILABLE)
	{

		m_infoList[index].m_rawData = m_msg.getDataSize();
		m_msg.resizeData(m_msg.getDataSize() + 3* 3*2 + 2);
		m_infoList[index].m_rawAcc = m_infoList[index].m_rawData;
		m_infoList[index].m_rawGyr = m_infoList[index].m_rawData + 3*2;
		m_infoList[index].m_rawMag = m_infoList[index].m_rawData + 6*2;
		m_infoList[index].m_rawTemp= m_infoList[index].m_rawData + 9*2;
		m_infoList[index].m_size += 3* 3*2 + 2;
	}

	int16_t* bare = (int16_t*) &data;
	for (uint16_t i=0;i<10;++i)
		m_msg.setDataShort(bare[i], m_infoList[index].m_rawData + (2*i));
	return true;
}
