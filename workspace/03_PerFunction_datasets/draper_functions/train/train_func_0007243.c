writeToStream(mrpt::utils::CStream &out,int *version) const
{
	if (version)
		*version = 1;
	else
	{
		writeToStreamRender(out);
		out << m_str;
        out << m_fontName;
        out << (uint32_t)m_fontHeight << (uint32_t)m_fontWidth;

	}
}
