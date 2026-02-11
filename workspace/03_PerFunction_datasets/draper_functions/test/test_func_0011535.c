runThread (void *arg)
{


	ArRobotPacket *packet;


	myScreenNumberChanged = false;
	myBootTextChanged = false;
	myChangedBootText[0] = '\0';
	myMainScreenStatusChanged = false;
	myChangedStatusText[0] = '\0';
	myMainScreenModeChanged = false;
	myChangedModeText[0] = '\0';
	myBackLightChanged = false;
	myIpAddress = "0.0.0.0";

	getIpAddress();

	setRobotIPStatus(myIpAddress.c_str());
	ArUtil::sleep(300);


while (getRunning() )
{

	if (myRobotIdentifierChanged) {
		setRobotIdStatus(myRobotIdentifier.c_str());
		myRobotIdentifierChanged = false;
		ArUtil::sleep(300);
	}

	if (myScreenNumberChanged) {
		setScreenNumber(myChangedScreenNumber);
		myScreenNumberChanged = false;
		ArUtil::sleep(300);
	}

	if (myBackLightChanged) {
		setBacklight(myChangedBackLight);
		myBackLightChanged = false;
		ArUtil::sleep(300);
	}

	if (myBootTextChanged) {
		setBootStatus(myChangedBootText);
		myBootTextChanged = false;
		myChangedBootText[0] = '\0';
		ArUtil::sleep(300);
	}

	if (myMainScreenStatusChanged) {
		setMainStatus(myChangedStatusText);
		myMainScreenStatusChanged = false;
		myChangedStatusText[0] = '\0';
		ArUtil::sleep(300);
	}

	if (myMainScreenModeChanged) {
		setTextStatus(myChangedModeText);
		myMainScreenModeChanged = false;
		myChangedModeText[0] = '\0';
		ArUtil::sleep(300);
	}


	if (!setSystemMeters(getBatteryPercentage(), getWifiPercentage())) {
		IFDEBUG(ArLog::log (ArLog::Normal,
									"%s::runThread() call to setSystemMeters failed", getName()));
	}

	ArUtil::sleep(300);


	if (!sendKeepAlive()) {
		IFDEBUG(ArLog::log (ArLog::Normal,
		            "%s::runThread() call to sendKeepAlive failed", getName()));
	}

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
		            "%s::runThread()  Lost connection to the MTX lcd because of error.  Nothing received for %g seconds (greater than the timeout of %g).", getName(),
		            myLastReading.mSecSince() / 1000.0,
		            getConnectionTimeoutSeconds() );
		myIsConnected = false;
		if (myConnFailOption)
			disconnectOnError();
		continue;
	}

}


	return NULL;
}
