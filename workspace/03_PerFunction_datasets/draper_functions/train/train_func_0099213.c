extractCylinder( const TPoint2D &center, const double radius, const double zmin, const double zmax, CPointsMap *outMap )
{
	outMap->clear();
	for( size_t k = 0; k < x.size(); k++ )
	{
		if( (z[k] <= zmax && z[k] >= zmin) && ( sqrt(square(center.x-x[k])+square(center.y-y[k])) < radius ) )
			outMap->insertPoint( x[k], y[k], z[k] );
	}
}
