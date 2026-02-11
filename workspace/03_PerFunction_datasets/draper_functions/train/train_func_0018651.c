newBase( GenericPlayer * player, GenericBase * base )
{

	AttalPlayerSocket * socket = findSocket( player );

	if( socket ) {
		socket->sendBaseNew( base );
		for( uint i = 0; i < base->getBuildingCount(); i++ ) {
			socket->sendBaseBuilding( base, base->getBuilding( i ), true );
		}
		for(int i = 0; i < MAX_UNIT; i++ ) {
			socket->sendBaseUnit( base, base->getUnit(i), i );
		}
		socket->sendBaseName( base );
	}
}
