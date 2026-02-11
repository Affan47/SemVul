updateOriMatrix(const CmtMatrix& data, const uint16_t index)
{
	const uint16_t numValues = 9;
	if (getDataSize(index) == 0)
		return false;

	uint16_t ds = getFPValueSize(index);

	if (m_infoList[index].m_oriMat == CMT_DATA_ITEM_NOT_AVAILABLE)
	{

		m_infoList[index].m_oriMat = m_msg.getDataSize();
		m_msg.resizeData(m_msg.getDataSize() + numValues*ds);
		m_infoList[index].m_size += numValues*ds;
	}

	uint16_t k = 0;
	for (int32_t i=0;i<3;++i)
		for (int32_t j=0;j<3;++j, k+=ds)
			m_msg.setDataFPValue(m_formatList[index].m_outputSettings, data.m_data[i][j], m_infoList[index].m_oriMat+k);
	return true;
}
