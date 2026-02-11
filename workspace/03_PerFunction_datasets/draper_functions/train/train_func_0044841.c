exchangeUnitSplit()
{
	uchar idLord = readChar();
	uchar idUnit = readChar();
	uchar num1 = readChar();
	uchar pos2 = readChar();
	uchar num2 = readChar();
	GenericLord * lord = NULL;

	TRACE("Engine::exchangeUnitSplit idLord %d, idUnit %d, pos1 %d, num1 %d, pos2 %d, num2 %d", idLord, idUnit, num1, pos2, num2);
	if( idLord ) {
		lord = _currentPlayer->getLordById( idLord );

		if( idUnit > MAX_UNIT && pos2 > MAX_UNIT ) {
			return;
		}

		GenericFightUnit * unit = lord->getUnit( idUnit );
		GenericFightUnit * unit2 = lord->getUnit( pos2 );

		TRACE(" unit %p", unit );

		if( ! unit2 && num2  ) {
			unit2 = new GenericFightUnit();
			unit2->setCreature( unit->getRace(), unit->getLevel() );
			unit2->setMove( unit->getMove() );
			unit2->setHealth( unit->getHealth() );
		}

		if( unit && !num1  ) {
			delete unit;
			unit = NULL;
		}

		if( unit2 && !num2  ) {
			delete unit;
			unit = NULL;
		}

		if( unit ) {
			unit->setNumber( num1 );
		}

		if( unit2 ) {
			unit2->setNumber( num2 );
		}

		lord->setUnit( idUnit, unit );
		lord->setUnit( pos2, unit2 );
		_server->updateUnits( _players, lord );
	}

}
