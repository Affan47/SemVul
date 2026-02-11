getBoundingBox(mrpt::math::TPoint3D &bb_min, mrpt::math::TPoint3D &bb_max) const
{
	bb_min.x = 10e10; bb_min.y = 10e10; bb_min.z = 10e10;
	bb_max.x = -10e10; bb_max.y = -10e10; bb_max.z = -10e10;

	for (unsigned int i=0; i<x_p.getColCount(); i++)
		for (unsigned int j=0; j<x_p.getRowCount(); j++)
		{

			if (x_p(j,i) < bb_min.x)
				bb_min.x = x_p(j,i);

			if (x_p(j,i) + x_vf(j,i) < bb_min.x)
				bb_min.x = x_p(j,i) + x_vf(j,i);

			if (y_p(j,i) < bb_min.y)
				bb_min.y = y_p(j,i);

			if (y_p(j,i) + y_vf(j,i) < bb_min.y)
				bb_min.y = y_p(j,i) + y_vf(j,i);

			if (z_p(j,i) < bb_min.z)
				bb_min.z = z_p(j,i);

			if (z_p(j,i) + z_vf(j,i) < bb_min.z)
				bb_min.z = z_p(j,i) + z_vf(j,i);


			if (x_p(j,i) > bb_max.x)
				bb_max.x = x_p(j,i);

			if (x_p(j,i) + x_vf(j,i) > bb_max.x)
				bb_max.x = x_p(j,i) + x_vf(j,i);

			if (y_p(j,i) > bb_max.y)
				bb_max.y = y_p(j,i);

			if (y_p(j,i) + y_vf(j,i) > bb_max.y)
				bb_max.y = y_p(j,i) + y_vf(j,i);

			if (z_p(j,i) > bb_max.z)
				bb_max.z = z_p(j,i);

			if (z_p(j,i) + z_vf(j,i) > bb_max.z)
				bb_max.z = z_p(j,i) + z_vf(j,i);
	}


	m_pose.composePoint(bb_min, bb_min);
	m_pose.composePoint(bb_max, bb_max);
}
