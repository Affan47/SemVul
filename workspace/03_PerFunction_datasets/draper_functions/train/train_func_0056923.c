slot_mouseMoved( GenericCell * c )
{
	if( _currentCell != c ) {
		updateStatusBar( c );
		if( c->getLord() ) {
			setCursor( Qt::WaitCursor );
		} else if( c->getBase() ) {
			setCursor( Qt::WaitCursor );
		} else if( c->getBuilding() ) {
			setCursor( Qt::WaitCursor );
		} else if( c->getEvent() ) {
			setCursor( Qt::WaitCursor );
		} else if( c->getCreature() ) {
			setCursor( Qt::WaitCursor );
		} else if( c->getDecorationGroup() ) {
			setCursor( Qt::PointingHandCursor );
		} else if( c->getCoeff() < 0  || !c->isStoppable() || !c->isFree() ) {
			setCursor( Qt::ForbiddenCursor );


		} else {
			setCursor( Qt::ArrowCursor );
		}

		_currentCell = c;
		if( _leftPressed ) {
			_selector->handleLeftClick( c );
			cellChanged( c );
		}

	}
}
