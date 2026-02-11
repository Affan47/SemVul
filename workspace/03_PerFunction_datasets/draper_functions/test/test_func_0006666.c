addCreatures( Creature * creature, int number )
{
	bool ret = false;

	for( int i = 0; i < MAX_UNIT; i++ ) {
		GenericFightUnit * unit = _units[i];
		if( unit == 0 ) {
			unit = new GenericFightUnit();
			unit->setCreature( creature );
			unit->setNumber( number );
			_units[i] = unit;
			ret = true;
			break;
		} else if( ( unit->getLevel() == creature->getLevel() )
			&& ( unit->getRace() == creature->getRace() ) ) {
			unit->addNumber( number );
			ret = true;
			break;
		}
	}

	return ret;
}
