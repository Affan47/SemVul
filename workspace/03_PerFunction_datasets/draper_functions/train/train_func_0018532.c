writeToStream(mrpt::utils::CStream &out,int *version) const
{

	if (version)
		*version = 2;
	else
	{
		writeToStreamRender(out);
		out << m_points;
		out << m_pointSize;
		out << m_pointSmooth;
	}
}
