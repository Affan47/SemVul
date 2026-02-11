GetFirstSupportedMimeType (std::list < std::string >::iterator &it)
{
	it = m_SupportedMimeTypes.begin ();
	return (it == m_SupportedMimeTypes.end ())? NULL: (*it).c_str ();
}
