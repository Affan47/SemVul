FR_vf2smpte(FrameRate *fr, char *smptestring, long int vf) {
	if (!smptestring) return;
	long int bcd[SMPTE_LAST];
	const char *fmt;

	FR_frame_to_bcd(fr, bcd, vf);


	if (FR_todbl(fr) <= 10) {
	  fmt= "%02li:%02li:%02li%c%01li";
	} else if (FR_todbl(fr) <= 100) {
	  fmt= "%02li:%02li:%02li%c%02li";
	} else {
	  fmt= "%02li:%02li:%02li%c%03li";
	}

	snprintf(smptestring,13,fmt,
			bcd[SMPTE_HOUR]%100,
			bcd[SMPTE_MIN],
			bcd[SMPTE_SEC],
			(fr->flags&FRF_DROP_FRAMES)?'.':':',
			bcd[SMPTE_FRAME]);
}
