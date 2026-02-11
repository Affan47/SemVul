truncateByDistanceAndAngle(float min_distance, float max_angle, float min_height, float max_height, float h )
{

	std::vector<float>::iterator		itScan;
	std::vector<char>::iterator itValid;
	CPose3D						pose;
	unsigned int				k;
	unsigned int				nPts = scan.size();

	for( itScan = scan.begin(), itValid = validRange.begin(), k = 0;
		 itScan != scan.end();
		 itScan++, itValid++, k++ )
	{
		float ang	= fabs(k*aperture/nPts - aperture*0.5);
		float x		= (*itScan)*cos(ang);

		if( min_height != 0 || max_height != 0 )
		{
			ASSERT_( max_height > min_height );
			if( *itScan < min_distance || ang > max_angle || x > h - min_height || x < h - max_height )
				*itValid = false;
		}
		else
			if( *itScan < min_distance || ang > max_angle )
				*itValid = false;
	}
}
