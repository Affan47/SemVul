getScreenNumber(unsigned char *currentScreenNumber)

{
	ArRobotPacket sendPacket(HEADER1, HEADER2);
	sendPacket.setID (GET_CURRENT_SCREEN_NUM);

	for (int i = 0; i < 5; i++) {

		if (!mySender->sendPacket(&sendPacket)) {
			ArLog::log (ArLog::Terse,
									"%s::getScreenNumber() Could not send get screen number to LCD", getName());
			return false;
		}

		IFDEBUG (

			ArLog::log (ArLog::Normal,
	              "%s::getScreenNumber() get screen number sent to LCD",
	              getName());

		);


		ArRobotPacket *packet = myReceiver->receivePacket (1000);

		if (packet == NULL) {
			ArLog::log (ArLog::Normal,
			            "%s::getScreenNumber() No response to get screen number - resending (%d)",
			            getName(), i);
			delete packet;
			continue;
		}

		unsigned char *screenStatusBuf = (unsigned char *) packet->getBuf();


		if (screenStatusBuf[3] != GET_CURRENT_SCREEN_NUM) {
			ArLog::log (ArLog::Normal,
			            "%s::getScreenNumber() Invalid response from lcd to get screen number (0x%x)",
			            getName(), screenStatusBuf[3]);
			continue;

		} else {
			*currentScreenNumber = screenStatusBuf[4];
			delete packet;
			return true;
		}
	}

	return false;

}
