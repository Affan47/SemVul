delEvent( const QList<GenericPlayer *> & list, GenericEvent * event )
{
	AttalPlayerSocket * socket;

	uint nbSockets = (uint) list.count();
	for( uint k = 0; k < nbSockets; ++k ) {
		socket = findSocket(list.at(k));
		if( socket->canSee( event->getCell() ) ) {
			socket->sendDelEvent( event );
		}
	}

}
