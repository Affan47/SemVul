characters( const QString& ch )
{
	QString ch_simplified = ch.simplified();
	if ( ch_simplified.isEmpty() )
		return true;

	switch( _state ) {
	case StateName:
		_position->setName( ch_simplified );
		break;
	default:
	    return false;
    }

    return true;
}
