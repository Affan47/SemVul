getNewBuilding( uchar type )
{
	GenericBuilding * ret = new GenericBuilding( type );
	_buildings.append( ret );
	return ret;
}
