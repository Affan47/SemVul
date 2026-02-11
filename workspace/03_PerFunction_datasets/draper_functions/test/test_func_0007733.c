turn_closed()
	{
		if(debugLevel >= IceTransport::DL_Info)
			emit q->debugLine("turn_closed");

		emit q->stopped();
	}
