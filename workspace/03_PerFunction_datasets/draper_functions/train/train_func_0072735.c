runThread (void *arg)
{

	ArRobotPacket *packet;

while (getRunning() )
{

	while (getRunning() && myIsConnected &&
	       (packet = myReceiver->receivePacket (500)) != NULL) {
		myPacketsMutex.lock();
		myPackets.push_back (packet);
		myPacketsMutex.unlock();
		if (myRobot == NULL)
			sensorInterp();
	}


	if (getRunning() && myIsConnected && checkLostConnection() ) {
		ArLog::log (ArLog::Terse,
		            "%s::runThread()  Lost connection to the MTX battery because of error.  Nothing received for %g seconds (greater than the timeout of %g).", getName(),
		            myLastReading.mSecSince() / 1000.0,
		            getConnectionTimeoutSeconds() );
		myIsConnected = false;
		disconnectOnError();
		continue;
	}

}


	return NULL;
}
