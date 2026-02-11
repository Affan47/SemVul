setDiversification( uint divers )
{
	if( divers < DataTheme.tiles.at( _type )->getDiversificationNumber() ) {
		_divers = divers;
	} else {
		_divers = 0;
	}
}
