startFight( int lordAttack, GenericMapCreature * creature )
{
	if( !_fight ) {
		_fight = new FightEngine( _server );
		QObject::connect( _fight, SIGNAL( sig_endFight( FightResultStatus ) ), SLOT( slot_endFight( FightResultStatus ) ) );
	}
	_state = IN_FIGHT;
	_fight->setDefendCell( creature->getCell() );
	GenericFightUnit * units[MAX_UNIT];
	for( int i = 0; i < MAX_UNIT; i++ ) {
		if( creature->getStack( i ) > 0 ) {
			units[i] = new GenericFightUnit();
			units[i]->setCreature( creature->getCreature() );
			units[i]->setNumber( creature->getStack( i ) );
		} else {
			units[i] = NULL;
		}
	}

	_fight->init( _currentPlayer, _currentPlayer->getLordById( lordAttack ), units, (GameData *)this );


	TRACE( "start fight finished" );
}
