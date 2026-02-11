removeRace()
{
	delete DataTheme.creatures.takeAt( _race );
	int newRace = std::min( _race, DataTheme.creatures.countRace() - 1 );
	int newCreature = std::min( (int) _creature, DataTheme.creatures.getRace( newRace )->count() - 1 );

	for( int i = 0; i < DataTheme.lords.count(); i++ ) {
		GenericLordModel * lord = DataTheme.lords.at( i );

		for( uint j = 0; j < MAX_UNIT; j++ ) {
			GenericFightUnit * unit = lord->getUnit( j );
			if( ( unit ) && ( unit->getRace() == _race ) ) {
				unit->setCreature( newRace, newCreature );
			}
		}
	}

	_race = newRace;
}
