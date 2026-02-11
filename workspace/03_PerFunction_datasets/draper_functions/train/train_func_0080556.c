updateData()
{
	int race = _race->currentItem();

	_race->clear();
	for( uint i = 0; i < DataTheme.countRace(); i++ ) {
		_race->insertItem( DataTheme.creatures.getRace( i )->getName() );
	}
	if( _unit ) {
		_race->setCurrentItem( _unit->getRace() );
	} else {
		_race->setCurrentItem( race );
	}

	_name->clear();
	if(_race->currentItem() >= 0) {
		for( int i = 0; i < DataTheme.creatures.getRace( _race->currentItem() )->count(); i++ ) {
			_name->insertItem( DataTheme.creatures.getRace( _race->currentItem() )->at( i )->getName() );
		}
	}
}
