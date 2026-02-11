smpte_set_timezone_string(LTCFrame *frame, SMPTETimecode *stime) {
	int i = 0;

	const unsigned char code = frame->user7 + (frame->user8 << 4);

	char timezone[6] = "+0000";

	for (i = 0 ; smpte_time_zones[i].code != 0xFF ; i++) {
		if ( smpte_time_zones[i].code == code ) {
			strcpy(timezone, smpte_time_zones[i].timezone);
			break;
		}
	}
	strcpy(stime->timezone, timezone);
}
