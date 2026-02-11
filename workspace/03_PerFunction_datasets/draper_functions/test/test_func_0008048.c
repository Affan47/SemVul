getLordById( int id )
{
    	for( uint i = 0; i < numLord(); i++ ) {
		if( _theLords.at( i )->getId() == id ) {
			return _theLords.at( i );
		}
	}
	return 0;
}
