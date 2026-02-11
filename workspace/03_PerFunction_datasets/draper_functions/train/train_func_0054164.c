set_translation(float x, float y, bool offset_points)
{
	CL_Pointf old_position = position;

	if( !offset_points )
	{
		position.x = x;
		position.y = y;
	}

	CL_Pointf translation;

	if( offset_points )
	{
		translation.x = x;
		translation.y = y;
	}
	else
		translation = (position - old_position);

	std::vector<CL_Contour>::iterator it;
	for( it = contours.begin(); it != contours.end(); ++it )
	{
		std::vector<CL_Pointf>::iterator ita;
		for( ita = (*it).points.begin(); ita != (*it).points.end(); ++ita )
			(*ita) += translation;
	}

	for( it = contours.begin(); it != contours.end(); ++it )
	{
		std::vector<CL_OutlineCircle>::iterator ita;
		for( ita = (*it).sub_circles.begin(); ita != (*it).sub_circles.end(); ++ita )
		{
			(*ita).position += translation;
		}
	}

	minimum_enclosing_disc.position += translation;
}
