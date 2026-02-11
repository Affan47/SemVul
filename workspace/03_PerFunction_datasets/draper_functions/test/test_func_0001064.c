ReadFromSocket(CECSocket& socket)
{
	ec_tagname_t tmp_tagName;
	if (!socket.ReadNumber(&tmp_tagName, sizeof(ec_tagname_t))) {
		return false;
	}
	m_tagName = tmp_tagName >> 1;
	bool hasChildren = (tmp_tagName & 0x01) != 0;

	if (!socket.ReadNumber(&m_dataType, sizeof(ec_tagtype_t))) {
		return false;
	}

	if (!socket.ReadNumber(&m_dataLen, sizeof(ec_taglen_t))) {
		return false;
	}

	if (hasChildren && !ReadChildren(socket)) {
		return false;
	}

	unsigned int tmp_len = m_dataLen;
	m_dataLen = 0;
	m_dataLen = tmp_len - GetTagLen();
	if (m_dataLen > 0) {
		NewData();
		if (!socket.ReadBuffer(m_tagData, m_dataLen)) {
			return false;
		}
	} else {
		m_tagData = NULL;
	}

	return true;
}
