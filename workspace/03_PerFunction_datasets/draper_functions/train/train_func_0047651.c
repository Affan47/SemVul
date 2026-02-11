slot_accept()
{
	if( _condition ) {
		if( _radioDate->isChecked() ) {
			_condition->setConditionDate( _day->value(), _week->value(), _month->value(), _year->value() );
		} else {
			_condition->setConditionDelay( _delay->value() );
		}
	}
	accept();
}
