readFromStream(mrpt::utils::CStream &in,int version)
{
	switch(version)
	{
	case 0:
		{

			CMatrix  HM2;
			in >> HM2;
			ASSERT_(mrpt::math::size(HM2,1)==4 && HM2.isSquare())

			m_ROT = HM2.block(0,0,3,3).cast<double>();

			m_coords[0] = HM2.get_unsafe(0,3);
			m_coords[1] = HM2.get_unsafe(1,3);
			m_coords[2] = HM2.get_unsafe(2,3);
			m_ypr_uptodate = false;
		} break;
	case 1:
		{

			CMatrixDouble44 HM;
			in >> HM;

			m_ROT = HM.block(0,0,3,3);

			m_coords[0] = HM.get_unsafe(0,3);
			m_coords[1] = HM.get_unsafe(1,3);
			m_coords[2] = HM.get_unsafe(2,3);
			m_ypr_uptodate = false;
		} break;
	case 2:
		{

			CPose3DQuat p(UNINITIALIZED_QUATERNION);
			in >>p[0]>>p[1]>>p[2]>>p[3]>>p[4]>>p[5]>>p[6];


			m_ypr_uptodate = false;
			m_coords[0] = p.x();
			m_coords[1] = p.y();
			m_coords[2] = p.z();
			p.quat().rotationMatrixNoResize(m_ROT);
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};
}
