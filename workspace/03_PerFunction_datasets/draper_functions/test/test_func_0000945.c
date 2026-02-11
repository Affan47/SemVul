getBoundingBox(mrpt::math::TPoint3D &bb_min, mrpt::math::TPoint3D &bb_max) const
{

    TPoint3Df pts[8];
	for (int j=0;j<2;j++)
	{
    	const float r = j==0 ? m_min_distance : m_max_distance;
    	for (int i=0;i<4;i++)
			pts[4*j+i].x = r;
		pts[4*j+0].y = -r*tan(m_fov_horz_left);
		pts[4*j+1].y = -r*tan(m_fov_horz_left);
		pts[4*j+2].y =  r*tan(m_fov_horz_right);
		pts[4*j+3].y =  r*tan(m_fov_horz_right);
		pts[4*j+0].z = -r*tan(m_fov_vert_down);
		pts[4*j+1].z =  r*tan(m_fov_vert_up);
		pts[4*j+2].z = -r*tan(m_fov_vert_down);
		pts[4*j+3].z =  r*tan(m_fov_vert_up);
    }

	bb_min = TPoint3D( std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max() );
	bb_max = TPoint3D(-std::numeric_limits<double>::max(),-std::numeric_limits<double>::max(),-std::numeric_limits<double>::max() );
	for (int i=0;i<8;i++)
	{
		keep_min(bb_min.x, pts[i].x);
		keep_min(bb_min.y, pts[i].y);
		keep_min(bb_min.z, pts[i].z);

		keep_max(bb_max.x, pts[i].x);
		keep_max(bb_max.y, pts[i].y);
		keep_max(bb_max.z, pts[i].z);
	}


	m_pose.composePoint(bb_min, bb_min);
	m_pose.composePoint(bb_max, bb_max);
}
