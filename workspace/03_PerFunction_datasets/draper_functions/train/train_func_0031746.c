RunFilter(mac_addr bssidmac, mac_addr sourcemac,
						  mac_addr destmac) {
	int hit = 0;


	macmap<int>::iterator fitr = bssid_map.find(bssidmac);

	if ((fitr != bssid_map.end() && bssid_invert == 1) ||
		(fitr == bssid_map.end() && bssid_invert == 0)) {
		bssid_hit++;
		hit = 1;
	}

	fitr = source_map.find(sourcemac);
	if ((fitr != source_map.end() && source_invert == 1) ||
		(fitr == source_map.end() && source_invert == 0)) {
		source_hit++;
		hit = 1;
	}

	fitr = dest_map.find(destmac);
	if ((fitr != dest_map.end() && dest_invert == 1) ||
		(fitr == dest_map.end() && dest_invert == 0)) {
		dest_hit++;
		hit = 1;
	}

	return hit;
}
