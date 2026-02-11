escapeURL ()
{
	if(!m_psz || !*m_psz)
		return;

	xmlChar * uri = xmlURIEscape(BAD_CAST m_psz);
	if(uri) {
		assign((gchar*)uri);
		xmlFree(uri);
	}
}
