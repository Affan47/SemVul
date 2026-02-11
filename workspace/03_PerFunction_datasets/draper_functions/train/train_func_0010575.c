doEvaluate() const
{
	QString s = arg( 0 )->evaluate().toString().string();
	long pos = long( qRound( arg( 1 )->evaluate().toNumber() ) );
	bool haveLength = argCount() == 3;
	long len = -1;
	if ( haveLength ) {
		len = long( qRound( arg( 2 )->evaluate().toNumber() ) );
	}

	if ( pos > long( s.length() ) ) {
		return Value( DOMString() );
	}

	if ( haveLength && pos < 1 ) {
		len -= 1 - pos;
		pos = 1;
		if ( len < 1 ) {
			return Value( DOMString() );
		}
	}

	return Value( DOMString( s.mid( pos - 1, len ) ) );
}
