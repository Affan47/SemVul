mlinkrxCharIn(radioInstance_t *r, uint8_t c) {
	unsigned long receiveTime = timerMicros();
	int i;
	int val;


	if (receiveTime - mlinkrxData.lastCharReceived > 7500) {
		mlinkrxData.count = 0;
	}

	mlinkrxData.lastCharReceived = timerMicros();


	mlinkrxData.framebuf[mlinkrxData.count] = c;
	mlinkrxData.count++;


	if (mlinkrxData.count == MLINKRX_FRAMESIZE) {

		mlinkrxData.count = 0;

		mlinkrxData.crc_calc = 0;

		for (i = 0; i < (MLINKRX_FRAMESIZE - 2); i++) {
			mlinkrxData.crc_calc = mpxCRC(mlinkrxData.crc_calc, mlinkrxData.framebuf[i]);
		}


		mlinkrxData.crc_rx = ((uint16_t)mlinkrxData.framebuf[MLINKRX_FRAMESIZE-2] << 8) + (uint16_t)mlinkrxData.framebuf[MLINKRX_FRAMESIZE-1];


		if (mlinkrxData.crc_calc == mlinkrxData.crc_rx) {

			for (i = 0; i < MLINKRX_CHANNELS; i++) {

				mlinkrxData.framebuf[2*i+1] &= 0x0F;


				val = (((uint16_t)mlinkrxData.framebuf[2*i+1] << 8) + (uint16_t)mlinkrxData.framebuf[2*i+2]) >> 1;
				if (&RADIO_THROT == &r->channels[i]) {
					r->channels[i] = val - 338;
				} else {
					r->channels[i] = val - 1024;
				}
			}
		} else {
			return 0;
		}
	}

	return 1;
}
