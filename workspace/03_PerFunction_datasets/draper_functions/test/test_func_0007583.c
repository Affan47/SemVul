init_concord()
{
	int err;
	rmt = NULL;

#ifdef WIN32

	WSADATA wsainfo;
	int error = WSAStartup(1*256 + 1, &wsainfo);
	if (error) {
		debug("WSAStartup() Error: %i", error);
		return LC_ERROR_OS_NET;
	}
#endif

	if (InitUSB()) {
		return LC_ERROR_OS;
	}

	if ((err = FindRemote(hid_info))) {
		hid_info.pid = 0;

		if ((err = FindUsbLanRemote())) {
			return LC_ERROR_CONNECT;
		}

		rmt = new CRemoteZ_USBNET;
	}


	if (hid_info.pid == 0xC11F) {
		return LC_ERROR_INVALID_DATA_FROM_REMOTE;
	}

	if (!rmt) {
		if (hid_info.pid >= ZWAVE_HID_PID_MIN &&
		    hid_info.pid <= ZWAVE_HID_PID_MAX) {

			rmt = new CRemoteZ_HID;
		} else if (is_mh_pid(hid_info.pid)) {
			rmt = new CRemoteMH;
		} else {
			rmt = new CRemote;


			rmt->Reset(COMMAND_RESET_USB);
		}
	}

	return 0;
}
