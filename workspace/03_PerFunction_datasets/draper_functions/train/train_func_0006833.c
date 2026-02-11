readFromStream(mrpt::utils::CStream &in,int version)
{
	switch(version)
	{
		case 0:
			readFromStreamRender(in);

			in >> xcomp >> ycomp;
			in >> xMin >> xMax >> yMin >> yMax;
			in >> m_LineWidth;
			in >> m_pointSize;
			in >> m_antiAliasing;
			in >> m_point_color;
			in >> m_field_color;
			break;

		default:
			MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
			break;
	};
	CRenderizableDisplayList::notifyChange();
}
