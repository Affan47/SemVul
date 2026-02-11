readFromStream(mrpt::utils::CStream &in, int version)
{
	switch(version)
	{
	case 0:
		{
			uint32_t	n;

			clear();

			in >> n;
			m_actions.resize(n);
			for_each( begin(),end(), ObjectReadFromStream(&in) );

		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};
}
