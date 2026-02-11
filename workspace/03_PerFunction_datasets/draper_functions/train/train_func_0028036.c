SetEncodingType(enum CharsetEncoding type, const wxString& encoding )
{
	if (type == ENCODING_CUSTOM && encoding == _T(""))
		return false;

	m_encodingType = type;
	m_customEncoding = encoding;

	return true;
}
