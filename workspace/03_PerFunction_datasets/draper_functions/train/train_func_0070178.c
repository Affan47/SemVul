ReQuery()
{
	CECPacket request(EC_OP_GET_STATSGRAPHS);

	request.AddTag(CECTag(EC_TAG_STATSGRAPH_WIDTH, (uint16)m_size));

	uint16 m_nGraphScale = 1;
	request.AddTag(CECTag(EC_TAG_STATSGRAPH_SCALE, m_nGraphScale));
	if (m_LastTimeStamp > 0.0) {
		request.AddTag(CECTag(EC_TAG_STATSGRAPH_LAST, m_LastTimeStamp));
	}

	const CECPacket *response = m_iface->SendRecvMsg_v2(&request);

	m_LastTimeStamp = response->GetTagByNameSafe(EC_TAG_STATSGRAPH_LAST)->GetDoubleData();

	const CECTag *dataTag = response->GetTagByName(EC_TAG_STATSGRAPH_DATA);
	const uint32 *data = (const uint32 *)dataTag->GetTagData();
	unsigned int count = dataTag->GetTagDataLen() / sizeof(uint32);

#if 0
	for (unsigned int i = 0; i < count; i += 4) {
#else

	for (unsigned int i = 0; i < count; i += 5) {
#endif

		m_down_speed->PushSample(ENDIAN_NTOHL(data[i+0]));
		m_up_speed->PushSample(ENDIAN_NTOHL(data[i+1]));
		m_conn_number->PushSample(ENDIAN_NTOHL(data[i+2]));
		m_kad_count->PushSample(ENDIAN_NTOHL(data[i+3]));


		m_activeKADU_count->PushSample(ENDIAN_NTOHL(data[i+4]));

	}
}
