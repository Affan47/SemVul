RemoveDroneCmd(uint32_t in_cmdid) {
	map<unsigned int, drone_cmd_rec *>::iterator dcritr =
		drone_cmd_map.find(in_cmdid);

	if (dcritr == drone_cmd_map.end()) {
		return 0;
	}

	delete dcritr->second;
	drone_cmd_map.erase(dcritr);

	return 1;
}
