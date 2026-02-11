charactersLord( const QString& ch )
{
	bool ret = true;

	switch( _lordState ) {
	case LordStateCol:
		_col = ch.toInt();
		break;
	case LordStateRow:
		_row = ch.toInt();
		break;
	case LordStateCharac:
		_lord->setBaseCharac( _charac, ch.toInt() );
		break;
	case LordStateUnitRace:
		_race = ch.toInt();
		break;
	case LordStateUnitLevel:
		_level = ch.toInt();
		break;
	case LordStateUnitNumber:
		_number = ch.toInt();
		break;
	case LordStateUnitMove:
		_move = ch.toInt();
		break;
	case LordStateUnitHealth:
		_health = ch.toInt();
		break;
	case LordStateArtefactPosition:
		_lordArtefact->setPosition( ch.toInt() );
		break;
	case LordStateMachine:
		_machine = ch.toInt();
		break;
	default:
		ret = false;
	}
	return ret;
}
