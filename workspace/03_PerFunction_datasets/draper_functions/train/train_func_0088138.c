Netracker_Clicmd_ADDNETTAG(CLIENT_PARMS) {
	int persist = 0;

	if (parsedcmdline->size() < 4) {
		snprintf(errstr, 1024, "Illegal ADDNETTAG request, expected BSSID "
				 "PERSIST TAG VALUES");
		return -1;
	}

	mac_addr net = mac_addr((*parsedcmdline)[0].word.c_str());

	if (net.error) {
		snprintf(errstr, 1024, "Illegal ADDNETTAG request, expected BSSID "
				 "PERSIST TAG VALUES");
		return -1;
	}

	if ((*parsedcmdline)[1].word != "0")
		persist = 1;

	string content;
	for (unsigned int x = 3; x < parsedcmdline->size(); x++) {
		content += (*parsedcmdline)[x].word;
		if (x < parsedcmdline->size() - 1)
			content += " ";
	}

	((Netracker *) auxptr)->SetNetworkTag(net, (*parsedcmdline)[2].word, content,
										  persist);

	return 1;
}
