mpu6000DrateDecode(void) {
	volatile uint8_t *d = mpu6000Data.rxBuf;
	int32_t gyo[3];
	float divisor;
	int s, i;

	if (mpu6000Data.enabled) {
		for (i = 0; i < 3; i++) {
			gyo[i] = 0;
		}

		divisor = (float)MPU6000_DRATE_SLOTS;
		s = mpu6000Data.slot - 1;
		if (s < 0) {
			s = MPU6000_SLOTS - 1;
		}

		for (i = 0; i < MPU6000_DRATE_SLOTS; i++) {
			int j = s*MPU6000_SLOT_SIZE;


			if (s == mpu6000Data.slot && mpu6000Data.spiFlag == 0)	{
				divisor -= 1.0f;
			} else {
				gyo[0] += (int16_t)__rev16(*(uint16_t *)&d[j+9]);
				gyo[1] += (int16_t)__rev16(*(uint16_t *)&d[j+11]);
				gyo[2] += (int16_t)__rev16(*(uint16_t *)&d[j+13]);
			}

			if (--s < 0) {
				s = MPU6000_SLOTS - 1;
			}
		}

		divisor = 1.0f / divisor;

		mpu6000ScaleGyo(gyo, mpu6000Data.dRateRawGyo, divisor);
		mpu6000CalibGyo(mpu6000Data.dRateRawGyo, mpu6000Data.dRateGyo);
	}
}
