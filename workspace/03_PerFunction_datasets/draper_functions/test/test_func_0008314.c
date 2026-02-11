Protocol_KISDEV_TRACKINFO(PROTO_PARMS) {
	Devicetracker *tracker = (Devicetracker *) data;
	string scratch;

	cache->Filled(field_vec->size());

	for (unsigned int x = 0; x < field_vec->size(); x++) {
		unsigned int fnum = (*field_vec)[x];

		if (fnum > TRACKINFO_maxfield) {
			out_string = "\001Unknown field\001";
			return -1;
		}

		if (cache->Filled(fnum)) {
			out_string += cache->GetCache(fnum) + " ";
			continue;
		}

		scratch = "";

		switch (fnum) {
			case TRACKINFO_devices:
				scratch = IntToString(tracker->FetchNumDevices(KIS_PHY_ANY));
				break;
			case TRACKINFO_packets:
				scratch = IntToString(tracker->FetchNumPackets(KIS_PHY_ANY));
				break;
			case TRACKINFO_datapackets:
				scratch = IntToString(tracker->FetchNumDatapackets(KIS_PHY_ANY));
				break;
			case TRACKINFO_cryptpackets:
				scratch = IntToString(tracker->FetchNumCryptpackets(KIS_PHY_ANY));
				break;
			case TRACKINFO_errorpackets:
				scratch = IntToString(tracker->FetchNumErrorpackets(KIS_PHY_ANY));
				break;
			case TRACKINFO_filterpackets:
				scratch = IntToString(tracker->FetchNumFilterpackets(KIS_PHY_ANY));
				break;
			case TRACKINFO_packetrate:
				scratch = IntToString(tracker->FetchPacketRate(KIS_PHY_ANY));
				break;
		}

		cache->Cache(fnum, scratch);
		out_string += scratch + " ";
	}

	return 1;
}
