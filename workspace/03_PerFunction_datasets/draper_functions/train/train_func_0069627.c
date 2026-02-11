socketTurn()
{
	ialogV( "SO_TURN" );

	switch( _socket->getCla2() ) {


	case C_TURN_PLAY:
		socketTurnPlay();
		break;
	case C_TURN_END:
		ialogC( "Should not happen (SO_TURN/C_TURN_END)" );
		break;
	case C_TURN_LORD:
		ialogC( "Should not happen (SO_TURN/C_TURN_LORD)" );
		break;
	case C_TURN_PLORD:
		socketTurnLord();
		break;
	}
}
