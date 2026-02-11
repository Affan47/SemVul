getOut()
{
	if( _currentCell ) {
		_currentCell->setLord( NULL );
		GenericBase * base = _currentCell->getBase();
		if( base != 0 ) {
			if( base->getGarrisonLord() == this ) {
				base->removeGarrisonLord();
			} else if( base->getVisitorLord() == this ) {
				base->removeVisitorLord();
			}
		}
	}
}
