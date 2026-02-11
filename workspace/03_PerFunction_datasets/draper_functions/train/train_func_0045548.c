QRinput_convertData(QRinput *input)
{
	int bits;
	int ver;

	ver = QRinput_estimateVersion(input);
	if(ver > QRinput_getVersion(input)) {
		QRinput_setVersion(input, ver);
	}

	for(;;) {
		bits = QRinput_createBitStream(input);
		if(bits < 0) return -1;
		ver = QRspec_getMinimumVersion((bits + 7) / 8, input->level);
		if(ver < 0) {
			errno = EINVAL;
			return -1;
		} else if(ver > QRinput_getVersion(input)) {
			QRinput_setVersion(input, ver);
		} else {
			break;
		}
	}

	return 0;
}
