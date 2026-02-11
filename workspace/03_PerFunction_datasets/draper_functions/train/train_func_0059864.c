handleInGameTurn()
{
	switch( getCla2() ) {
		case C_TURN_PLAY:
			logEE( "Should not happen (Server : SO_TURN/C_TURN_PLAY)" );
			break;
		case C_TURN_LORD:{
			int type = readInt();
			_server->sendLordPlTurn( _currentPlayer, type );
			}
			break;
		case C_TURN_PLORD:
			logEE( "Should not happen (Server : SO_TURN/C_TURN_PLORD)" );
			break;
		case C_TURN_END:
			nextPlayer();
			break;
	}
}
