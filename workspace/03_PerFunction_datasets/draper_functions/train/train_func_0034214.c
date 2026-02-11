readFromStream(mrpt::utils::CStream &in,int version)
{
	switch(version)
	{
	case 0:
		{
			CPoint3D m;
			in >> m;
			mean = TPoint3D(m);

			CMatrix c;
			in >> c; cov = c.cast<double>();
		} break;
	case 1:
		{
			in >> mean >> cov;
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};
}
