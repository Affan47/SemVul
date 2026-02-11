mpu6000SetReg(uint8_t reg, uint8_t val) {
	((uint8_t *)&mpu6000TxBuf)[0] = MPU6000_WRITE_BIT | reg;
	((uint8_t *)&mpu6000TxBuf)[1] = val;

	mpu6000Data.spiFlag = 0;
	spiTransaction(mpu6000Data.spi, &mpu6000RxBuf, &mpu6000TxBuf, 2);

	while (!mpu6000Data.spiFlag)
		;
}
