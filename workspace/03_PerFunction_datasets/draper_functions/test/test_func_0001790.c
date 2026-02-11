writeToStream(mrpt::utils::CStream &out, int *version) const
{
	if (version)
		*version = 0;
	else
	{
		out << m_x2y << m_wrap2pi;
	}

}
