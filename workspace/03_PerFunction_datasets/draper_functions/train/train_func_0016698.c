point_inside_contour( const CL_Pointf &point, const CL_Contour &contour )
{

	if(contour.is_inside_contour)
		return false;

	float lineX[4];
	lineX[0] = point.x;
	lineX[1] = point.y+0.000f;
	lineX[2] = point.x+99999.0f;
	lineX[3] = point.y+0.000f;


	int num_intersections_x = 0;

	const std::vector<CL_Pointf> &points = contour.points;

	std::vector<CL_OutlineCircle>::const_iterator it;
	for( it = contour.sub_circles.begin();
		 it != contour.sub_circles.end();
		 ++it )
	{
		const CL_OutlineCircle &circle = (*it);

		float dist = fabs(circle.position.y - point.y);

		if( dist <= circle.radius )
		{


			for( unsigned int i=circle.start; i != circle.end; ++i )
			{
				float line2[4];
				line2[0] = points[ i    % points.size()].x;
				line2[1] = points[ i    % points.size()].y;
				line2[2] = points[(i+1) % points.size()].x;
				line2[3] = points[(i+1) % points.size()].y;

				if( CL_LineMath::intersects(lineX, line2, false) )
				{
					num_intersections_x++;
				}
			}
		}
	}

	if( num_intersections_x % 2 )
	{
		return true;
	}

	return false;
}
