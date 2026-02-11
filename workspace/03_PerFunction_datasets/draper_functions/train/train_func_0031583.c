readFromStream(mrpt::utils::CStream &in,int version)
{
	switch(version)
	{
	case 0:
		{
			readFromStreamRender(in);
			in >> m_x0 >> m_y0 >> m_z0;
			in >> m_x1 >> m_y1 >> m_z1;
			in >> m_headRatio >> m_smallRadius >> m_largeRadius;
		}
        break;
	case 1:
		{
			readFromStreamRender(in);
			in >> m_x0 >> m_y0 >> m_z0;
			in >> m_x1 >> m_y1 >> m_z1;
			in >> m_headRatio >> m_smallRadius >> m_largeRadius;
			in >> m_arrow_roll >> m_arrow_pitch >> m_arrow_yaw;
		}
		break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};
	CRenderizableDisplayList::notifyChange();
}
