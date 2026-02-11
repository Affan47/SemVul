manageSocketState( int num )
{
	if(! _isProcessing ) {
		_isProcessing = true;
		_currentData = _dataQueue.dequeue();
		_num = num;

		switch( _state ) {
			case NOT_PLAYING:
				stateNotPlaying( num );
				break;
			case IN_GAME:
				stateInGame( num );
				break;
			case IN_QUESTION:
				stateInQuestion( num );
				break;
			case IN_FIGHT:
				stateInFight( num );
				break;
		}

		_isProcessing = false;

		if( !_dataQueue.isEmpty() ) {
			manageSocketState( num );
		}
	}

}
