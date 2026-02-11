getBoundingBox(mrpt::math::TPoint3D &bb_min, mrpt::math::TPoint3D &bb_max) const
{
	bb_min.x = xMin;
	bb_min.y = yMin;
	bb_min.z = 0;

	bb_max.x = xMax;
	bb_max.y = yMax;
	bb_max.z = 0;

	const float x_cell_size = (xMax - xMin)/(xcomp.getColCount()-1);
	const float y_cell_size = (yMax - yMin)/(ycomp.getRowCount()-1);

	for (unsigned int i=0; i<xcomp.getColCount(); i++)
		for (unsigned int j=0; j<xcomp.getRowCount(); j++)
		{
			const float tri_side = 0.25*sqrt(xcomp(j,i)*xcomp(j,i) + ycomp(j,i)*ycomp(j,i));
			const float ang = ::atan2(ycomp(j,i), xcomp(j,i)) - 1.5708;

			if ( -sin(ang)*0.866*tri_side + xMin+i*x_cell_size + xcomp(j,i) < bb_min.x)
				bb_min.x = -sin(ang)*0.866*tri_side + xMin+i*x_cell_size + xcomp(j,i);

			if ( cos(ang)*0.866*tri_side + yMin+j*y_cell_size + ycomp(j,i) < bb_min.y)
				bb_min.y = cos(ang)*0.866*tri_side + yMin+j*y_cell_size + ycomp(j,i);

			if ( -sin(ang)*0.866*tri_side + xMin+i*x_cell_size + xcomp(j,i) > bb_max.x)
				bb_max.x = -sin(ang)*0.866*tri_side + xMin+i*x_cell_size + xcomp(j,i);

			if ( cos(ang)*0.866*tri_side + yMin+j*y_cell_size + ycomp(j,i) > bb_max.y)
				bb_max.y = cos(ang)*0.866*tri_side + yMin+j*y_cell_size + ycomp(j,i);
		}


	m_pose.composePoint(bb_min, bb_min);
	m_pose.composePoint(bb_max, bb_max);
}
