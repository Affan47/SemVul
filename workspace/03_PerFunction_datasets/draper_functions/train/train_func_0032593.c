validateTransducers()
{

	ArRobotPacket *packet;


	bool gotTransducerCount = false;
	unsigned char *transBuf;

	for (int i = 0; i < 10; i++) {
		if (!sendGetTransducerCount()) {
			ArLog::log (ArLog::Normal,
			            "%s::validateTransducers() Could not send gettransducercount to Sonar", getNameWithBoard());
			return false;
		}

		packet = myReceiver->receivePacket (1000);

		if (packet == NULL) {
			ArLog::log (ArLog::Normal,
			            "%s::validateTransducers() No response to get transducer count", getNameWithBoard());
			continue;
		}

		transBuf = (unsigned char *) packet->getBuf();


		if ( (transBuf[3] != GET_NUM_TRANDUCERS) || (transBuf[4] == 0)) {
			ArLog::log (ArLog::Normal,
			            "%s::validateTransducers() Invalid response from sonar to gettransducercount (0x%x 0x%x)",
			            getNameWithBoard(), transBuf[3], transBuf[4]);
			continue;

		} else {
			gotTransducerCount = true;
			break;
		}
	}

	if (!gotTransducerCount) {
		ArLog::log (ArLog::Normal,
		            "%s::validateTransducers() Cannot get transducer count - exiting",
		            getNameWithBoard());
		return false;
	}

	gotTransducerCount = false;
	myNumTransducers = transBuf[4];
	ArLog::log (ArLog::Normal,
	            "%s::validateTransducers() Sonar has %d transducers", getNameWithBoard(), myNumTransducers);

	if (myNumTransducers < myNumConfiguredTransducers) {
		ArLog::log (ArLog::Normal,
		            "%s::validateTransducers() there are more transducers configured %d then there are on the board %d",
		            getNameWithBoard(), myNumConfiguredTransducers, myNumTransducers);
		return false;
	}

	delete packet;
	return true;
}
