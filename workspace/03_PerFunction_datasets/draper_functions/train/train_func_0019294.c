handleDelete()
{
	if( _currentCell->getLord() ) {
		GenericLord * lord = _currentCell->getLord();
		if(lord->getOwner()){
			lord->getOwner()->removeLord(lord);
		}
		lord->setCell( NULL );
	} else if( _currentCell->getCreature() ) {
		GenericMapCreature * creature = _currentCell->getCreature();
		removeMapCreature(creature);
		_currentCell->setCreature( NULL );
	} else if( _currentCell->getBuilding() ) {
		GenericBuilding * build = _currentCell->getBuilding();
		removeBuilding( build );
		_currentCell->setBuilding( NULL );
	} else if( _currentCell->getBase() ) {
		GenericBase * base = _currentCell->getBase();
		removeBase(  base );
		_currentCell->setBase( NULL );
	} else if( _currentCell->getEvent() ) {
		Event * event = (Event *)( _currentCell->getEvent() );
		removeEvent( event );
		_currentCell->setEvent( NULL );
	} else if( _currentCell->getDecorationGroup() ) {
		_currentCell->setDecoration( 0, 0 );
	} else if( _currentCell->getTransition() ) {
		_currentCell->setTransition( 0 );
		_currentCell->setTransitionCellType( 0 );
	}
	cellChanged( _currentCell );
}
