getSystemInfo()
{

	ArRobotPacket *packet;

	bool gotPacket = false;
	unsigned char *buf;
	for (int i = 0; i < 5; i++) {
		if (!sendSystemInfo (SEND_ONCE)) {
			ArLog::log (ArLog::Normal,
			            "%s::getSystemInfo() Could not send system info to battery",
			            getName());
			return false;
		}
		myAsyncConnectState = 0;

		packet = myReceiver->receivePacket (1000);
		if (packet == NULL) {
			ArLog::log (ArLog::Normal,
			            "%s::getSystemInfo() No response to get system info - resending", getName());
			continue;
		}
		buf = (unsigned char *) packet->getBuf();


		if ( (packet->getID() != SYSTEM_INFO) || (packet->getLength() != SYSTEM_INFO_SIZE)) {
			ArLog::log (ArLog::Normal,
			            "%s::getSystemInfo() Invalid response from battery to get system info (0x%x 0x%x)",
			            getName(), packet->getID(), packet->getLength());
			delete packet;
			continue;
		} else {
			updateSystemInfo (&buf[3]);
			delete packet;
			gotPacket = true;
			break;
		}
	}
	if (!gotPacket) {
		ArLog::log (ArLog::Normal,
		            "%s::getSystemInfo() Cannot get system info from battery",
		            getName());
		return false;
	}
	IFDEBUG (
	  ArLog::log (ArLog::Normal,
	              "%s::getSystemInfo() - successful", getName()));
	return true;
}
