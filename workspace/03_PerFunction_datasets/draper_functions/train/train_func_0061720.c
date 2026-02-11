containsProperly( const geom::Geometry* g) const
{

    if ( !envelopeCovers( g) )
		return false;

	return PreparedPolygonContainsProperly::containsProperly( this, g);
}
