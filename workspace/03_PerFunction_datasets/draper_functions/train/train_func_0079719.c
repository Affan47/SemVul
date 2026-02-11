readFromStream(mrpt::utils::CStream &in,int version)
{
	switch(version)
	{
	case 0:
		{
			float f;
			in >> f; m_coords[0]=f;
			in >> f; m_coords[1]=f;
			in >> f; m_coords[2]=f;
		} break;
	case 1:
		{

			in >> m_coords[0] >> m_coords[1] >> m_coords[2];
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};
}
