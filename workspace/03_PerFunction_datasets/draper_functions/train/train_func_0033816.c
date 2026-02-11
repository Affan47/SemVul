getDisposition( uint row, uint col )
{
	GenericBuildingModel * model = DataTheme.buildings.at( _type );
	if( model ) {
		return model->getDisposition( row, col );
	} else {
		return GenericMapDisposition::OCCUPIED;
	}
}
