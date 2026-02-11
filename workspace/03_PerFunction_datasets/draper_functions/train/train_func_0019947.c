ParseData(int in_fd) {
	int len, rlen;
	uint8_t *buf;
	ostringstream osstr;
	int pos = 0;
	int ret = 1;

	len = netserver->FetchReadLen(in_fd);


	if ((unsigned int) len < sizeof(drone_packet))
		return 0;

	buf = new uint8_t[len + 1];

	if (netserver->ReadData(in_fd, buf, len, &rlen) < 0) {
		osstr << "DroneFramework::ParseData failed to fetch data from "
			"client id " << in_fd;
		_MSG(osstr.str(), MSGFLAG_ERROR);
		delete[] buf;
		return -1;
	}

	if ((unsigned int) rlen < sizeof(drone_packet)) {
		delete[] buf;
		return 0;
	}

	while ((rlen - pos) >= (int) sizeof(drone_packet)) {
		drone_packet *dpkt = (drone_packet *) &(buf[pos]);

		if (kis_ntoh32(dpkt->sentinel) != DroneSentinel) {
			osstr << "DroneFramework::ParseData failed to find sentinel "
				"value in packet header, dropping connection to client " << in_fd;
			_MSG(osstr.str(), (MSGFLAG_ERROR | MSGFLAG_LOCAL));
			delete[] buf;
			return -1;
		}

		unsigned int dplen = kis_ntoh32(dpkt->data_len);


		if (rlen - (int) pos < (int) (dplen + sizeof(drone_packet))) {
			delete[] buf;
			return 0;
		}


		netserver->MarkRead(in_fd, (dplen + sizeof(drone_packet)));

		unsigned int dcid = kis_ntoh32(dpkt->drone_cmdnum);


		map<unsigned int, drone_cmd_rec *>::iterator dcritr =
			drone_cmd_map.find(dcid);
		if (dcritr == drone_cmd_map.end()) {
			osstr << "DroneFramework::ParseData got unknown packet type " <<
				dcid << "(" << hex << setprecision(4) << dcid << ")";
			_MSG(osstr.str(), (MSGFLAG_INFO | MSGFLAG_LOCAL));
		} else {
			if (dcritr->second->callback == NULL) {
				osstr << "DroneFramework::ParseData throwing away packet of known "
					"type " << dcid << " (" << hex << setprecision(4) << dcid << ") "
					"with no handler";
				_MSG(osstr.str(), (MSGFLAG_INFO | MSGFLAG_LOCAL));
			} else {
				ret =
					(*dcritr->second->callback)(globalreg, dpkt,
												dcritr->second->auxptr);
			}
		}

		pos += dplen + sizeof(drone_packet);
	}

	delete[] buf;

	return ret;
}
