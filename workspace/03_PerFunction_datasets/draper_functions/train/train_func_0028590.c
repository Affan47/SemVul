operator=(const CCertificate &op)
{
	if (&op == this)
		return *this;

	delete [] m_rawData;
	if (op.m_rawData)
	{
		wxASSERT(op.m_len);
		if (op.m_len)
		{
			m_rawData = new unsigned char[op.m_len];
			memcpy(m_rawData, op.m_rawData, op.m_len);
		}
		else
			m_rawData = 0;
	}
	else
		m_rawData = 0;
	m_len = op.m_len;

	m_activationTime = op.m_activationTime;
	m_expirationTime = op.m_expirationTime;

	m_serial = op.m_serial;
	m_pkalgoname = op.m_pkalgoname;
	m_pkalgobits = op.m_pkalgobits;

	m_signalgoname = op.m_signalgoname;

	m_fingerprint_md5 = op.m_fingerprint_md5;
	m_fingerprint_sha1 = op.m_fingerprint_sha1;

	m_subject = op.m_subject;
	m_issuer = op.m_issuer;

	return *this;
}
