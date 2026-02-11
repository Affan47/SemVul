end ()
{
	if (!sync ())
		return 0;
	return m_utfbuf + m_strbuf->byteLength ();
}
