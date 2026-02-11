setValue(const unsigned char *pc, unsigned long ulLen)
{
	if (m_Attr.pValue)
		::free(m_Attr.pValue);

	m_Attr.pValue = ::malloc(ulLen);
	ErrorEx::checkOutOfMemory(m_Attr.pValue);
	::memcpy(m_Attr.pValue, pc, ulLen);
	m_Attr.ulValueLen = ulLen;
}
