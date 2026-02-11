DisconnectPorts( const std::string & producer, const std::string & consumer)
	{
		_flowControl->NetworkTopologyChanged();

		OutPortBase & outport = GetOutPortByCompleteName(producer);
		InPortBase & inport = GetInPortByCompleteName(consumer);

		if ( !outport.IsVisuallyConnectedTo(inport))
			return false;

		if (!IsStopped()) Stop();

		outport.DisconnectFromIn( inport );
		return true;
	}
