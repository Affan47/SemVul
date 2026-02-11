get_latency(void) {
	rfbClientIteratorPtr iter;
	rfbClientPtr cl;
	int ilat, ilat_min = 1;
	int ilat_max = 2000;
	double slowest = -1.0, lat;
	static double save_lat = ((double) LATENCY0)/1000.0;
	int count = 0;

	if (!screen) {
		return 0;
	}

	iter = rfbGetClientIterator(screen);
	while( (cl = rfbClientIteratorNext(iter)) ) {
		ClientData *cd = (ClientData *) cl->clientData;

		if (! cd) {
			continue;
		}
		if (cl->state != RFB_NORMAL) {
			continue;
		}
		if (cd->latency == 0.0) {
			continue;
		}
		count++;

		lat = cd->latency;
		if (slowest == -1.0 || lat > slowest) {
			slowest = lat;
		}
	}
	rfbReleaseClientIterator(iter);

	if (! count) {
		return LATENCY0;
	}

	if (slowest == -1.0) {
		slowest = save_lat;
	} else {
		save_lat = slowest;
	}

	ilat = (int) (slowest * 1000.0);
	if (ilat < ilat_min) {
		ilat = ilat_min;
	}
	if (ilat > ilat_max) {
		ilat = ilat_max;
	}

	return ilat;
}
