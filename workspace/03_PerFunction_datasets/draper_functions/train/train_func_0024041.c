QRinput_convertData(QRinput *input, BitStream *bstream)
{
	int bits;
	int ver;

	ver = QRinput_estimateVersion(input);
	if(ver > QRinput_getVersion(input)) {
		QRinput_setVersion(input, ver);
	}

	for(;;) {
		BitStream_reset(bstream);
		bits = QRinput_createBitStream(input, bstream);
		if(bits < 0) return -1;
		ver = QRspec_getMinimumVersion((bits + 7) / 8, input->level);
		if(ver > QRinput_getVersion(input)) {
			QRinput_setVersion(input, ver);
		} else {
			break;
		}
	}

	return 0;
}
