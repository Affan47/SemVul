startFight( GenericPlayer * attacker,GenericLord * myLord, GenericPlayer * opponent, GenericLord * opponentLord )
{
	int i;

	AttalPlayerSocket * attackerSocket = findSocket( attacker );
	attackerSocket->sendFightInit( FIGHTER_ATTACK, myLord );
	attackerSocket->sendFightLord( FIGHTER_DEFENSE, opponentLord );
	for( i = 0; i < MAX_UNIT; i++ ) {
		if( opponentLord->getUnit( i ) ) {
			attackerSocket->sendFightNewUnit( FIGHTER_DEFENSE, i, opponentLord->getUnit( i ) );
		}
	}

	AttalPlayerSocket * opponentSocket = findSocket( opponent );
	opponentSocket->sendFightInit( FIGHTER_DEFENSE, opponentLord );
	opponentSocket->sendFightLord( FIGHTER_ATTACK, myLord );
	for( i = 0; i < MAX_UNIT; i++ ) {
		if( myLord->getUnit( i ) ) {
			opponentSocket->sendFightNewUnit( FIGHTER_ATTACK, i, myLord->getUnit( i ) );
		}
	}

}
