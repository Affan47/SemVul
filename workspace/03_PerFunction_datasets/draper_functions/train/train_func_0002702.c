init( GenericFightUnit * unit )
{
	_unit = unit;
	if( unit ) {
		_race->setCurrentItem( unit->getRace() );
		slot_raceChanged( unit->getRace() );
		_name->setCurrentItem( unit->getLevel() );
		_number->setValue( unit->getNumber() );
	} else {
		clear();
	}
}
