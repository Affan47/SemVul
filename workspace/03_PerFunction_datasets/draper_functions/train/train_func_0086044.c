socketQR()
{
	ialogV( "SO_QR" );
	switch( _socket->getCla2() ) {
	case C_QR_MSG_NEXT:
		socketQRMsgNext();
	 break;
	case C_QR_MSG_END:
		socketQRMsgEnd();
		break;
	case C_QR_LEVEL: {
		ialogV( "level" );

		} break;
	case C_QR_CHEST: {
		ialogV( "Chest" );
		_socket->sendAnswerEnum( 0 );
		sendLordTurn( C_ANALYST_SAME_LORD );
		} break;
	case C_QR_CREATURE_FLEE:
		_socket->sendAnswerYesNo( true );
		sendLordTurn( C_ANALYST_SAME_LORD );
		break;
	case C_QR_CREATURE_MERCENARY:
		_socket->sendAnswerYesNo( false );
		sendLordTurn( C_ANALYST_SAME_LORD );
		break;
	case C_QR_CREATURE_JOIN:
		_socket->sendAnswerYesNo( true );
		sendLordTurn( C_ANALYST_SAME_LORD );
		break;
	case C_QR_ANSWER:
		logEE( "Should not happen" );
		break;
	}

}
