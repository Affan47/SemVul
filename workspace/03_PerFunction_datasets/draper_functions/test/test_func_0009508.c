owReadByteISR(int bit) {
	if (bit < 0) {
		owData.byteValue = 0;
		owReadBitISR(OW_STATE_0);
		timerSetAlarm2(65, owReadByteISR, bit+1);
	} else {
		owData.byteValue |= (owData.bitValue<<bit);
		if (bit < 7) {
			owReadBitISR(OW_STATE_0);
			timerSetAlarm2(65, owReadByteISR, bit+1);
		}
	}
}
