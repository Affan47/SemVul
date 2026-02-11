iconStop()
	{
		if ( ic ) {
			disconnect(ic, 0, this, 0 );
			if ( animated ) {
				ic->stop();
				animated = false;
			}
		}
	}
