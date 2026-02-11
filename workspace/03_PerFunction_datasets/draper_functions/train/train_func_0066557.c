navClearWaypoints(void) {
	unsigned char ack = 0;
	int i;

	if (navData.mode != NAV_STATUS_MISSION) {
		for (i = 0; i < NAV_MAX_MISSION_LEGS; i++) {
			navData.missionLegs[i].type = 0;
		}
		ack = 1;
	}

	return ack;
}
