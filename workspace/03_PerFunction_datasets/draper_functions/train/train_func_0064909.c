settpref(u_int16_t *tpref, u_int16_t tag)
{
	int i;


	if (tag == EXIF_T_UNKNOWN) {
		settpref(tpref, EXIF_T_DATETIME);
		settpref(tpref, EXIF_T_DATETIMEORIG);
		settpref(tpref, EXIF_T_DATETIMEDIGI);
		return;
	}

	for (i = 0; i < 3; i++) {
		if (tpref[i] == tag)
			break;
		if (tpref[i] == EXIF_T_UNKNOWN) {
			tpref[i] = tag;
			break;
		}
	}
}
