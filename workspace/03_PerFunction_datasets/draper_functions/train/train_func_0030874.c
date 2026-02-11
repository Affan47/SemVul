updateStatus(const uint8_t data, const uint16_t index)
{
	if (getDataSize(index) == 0)
		return false;

	if (m_infoList[index].m_status == CMT_DATA_ITEM_NOT_AVAILABLE)
	{

		m_infoList[index].m_status = m_msg.getDataSize();
		m_msg.resizeData(m_msg.getDataSize() + 1);
		m_infoList[index].m_size += 1;
	}

	m_msg.setDataByte(data,m_infoList[index].m_status);
	return true;
}
