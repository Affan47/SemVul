manageCondition( const QString & type )
{
	_params.clear();
	if( _currentCondition ) {
		_conditionStack.push( (QuestConditionComposite *)_currentCondition );
	}

	if( type == "composite" ) {
		_currentCondition = new QuestConditionComposite();
	} else if( type == "lord" ) {
		_currentCondition = new QuestConditionLord();
	} else if( type == "date" ) {
		_currentCondition = new QuestConditionDate();
	} else if( type == "player" ) {
		_currentCondition = new QuestConditionPlayer();
	}

	if( _conditionStack.isEmpty() ) {
		switch( _oldQuestState ) {
		case QuestStart:
			_quest->setStartCondition( _currentCondition );
			break;
		case QuestFail:
			_quest->setFailCondition( _currentCondition );
			break;
		case QuestSuccess:
			_quest->setSuccessCondition( _currentCondition );
			break;
		default:
			logEE( "Should not happen" );
		}
	} else {
		_conditionStack.top()->addCondition( _currentCondition );
	}
}
