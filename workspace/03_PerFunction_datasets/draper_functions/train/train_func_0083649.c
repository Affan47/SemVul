updateRawGpsData(const CmtRawGpsData& data, const uint16_t index)
{
	if (getDataSize(index) == 0)
		return false;
	if (m_infoList[index].m_rawGpsData == CMT_DATA_ITEM_NOT_AVAILABLE)
	{

		m_infoList[index].m_rawGpsData = m_msg.getDataSize();
		m_msg.resizeData(m_msg.getDataSize() + (2+1) + (40 + 1));
		m_infoList[index].m_rawGpsPressure = m_infoList[index].m_rawGpsData;
		m_infoList[index].m_rawGpsPressureAge = m_infoList[index].m_rawGpsData + 2;

		m_infoList[index].m_rawGpsGpsData = m_infoList[index].m_rawGpsData + 3;
		m_infoList[index].m_rawGpsItow = m_infoList[index].m_rawGpsData + 3;
		m_infoList[index].m_rawGpsLatitude = m_infoList[index].m_rawGpsData + 3 + 4;
		m_infoList[index].m_rawGpsLongitude = m_infoList[index].m_rawGpsData + 3 + 8;
		m_infoList[index].m_rawGpsHeight = m_infoList[index].m_rawGpsData + 3 + 12;
		m_infoList[index].m_rawGpsVeln = m_infoList[index].m_rawGpsData + 3 + 16;
		m_infoList[index].m_rawGpsVele = m_infoList[index].m_rawGpsData + 3 + 20;
		m_infoList[index].m_rawGpsVeld = m_infoList[index].m_rawGpsData + 3 + 24;
		m_infoList[index].m_rawGpsHacc = m_infoList[index].m_rawGpsData + 3 + 28;
		m_infoList[index].m_rawGpsVacc = m_infoList[index].m_rawGpsData + 3 + 32;
		m_infoList[index].m_rawGpsSacc = m_infoList[index].m_rawGpsData + 3 + 36;
		m_infoList[index].m_rawGpsGpsAge = m_infoList[index].m_rawGpsData + 3 + 40;

		m_infoList[index].m_size += (2+1) + (40 + 1);
	}

	m_msg.setDataShort(data.m_pressure, m_infoList[index].m_rawGpsPressure);
	m_msg.setDataByte(data.m_pressureAge, m_infoList[index].m_rawGpsPressureAge);


	int32_t* bareln = (int32_t*)&data.m_itow;
	for (uint16_t i=0; i<10;++i)
		m_msg.setDataLong(bareln[i],m_infoList[index].m_rawGpsGpsData + (4*i));


	m_msg.setDataByte(data.m_gpsAge,  m_infoList[index].m_rawGpsGpsAge);
	return true;
}
