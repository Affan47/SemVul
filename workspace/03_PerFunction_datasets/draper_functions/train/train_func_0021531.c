dwEnableClock(dwDevice_t* dev, dwClock_t clock) {
	uint8_t pmscctrl0[LEN_PMSC_CTRL0];
	memset(pmscctrl0, 0, LEN_PMSC_CTRL0);
	dwSpiRead(dev, PMSC, PMSC_CTRL0_SUB, pmscctrl0, LEN_PMSC_CTRL0);
	if(clock == dwClockAuto) {
    dev->ops->spiSetSpeed(dev, dwSpiSpeedLow);
		pmscctrl0[0] = dwClockAuto;
		pmscctrl0[1] &= 0xFE;
	} else if(clock == dwClockXti) {
    dev->ops->spiSetSpeed(dev, dwSpiSpeedLow);
		pmscctrl0[0] &= 0xFC;
		pmscctrl0[0] |= dwClockXti;
	} else if(clock == dwClockPll) {
    dev->ops->spiSetSpeed(dev, dwSpiSpeedHigh);
		pmscctrl0[0] &= 0xFC;
		pmscctrl0[0] |= dwClockPll;
	} else {

	}
	dwSpiWrite(dev, PMSC, PMSC_CTRL0_SUB, pmscctrl0, 1);
  dwSpiWrite(dev, PMSC, PMSC_CTRL0_SUB, pmscctrl0, LEN_PMSC_CTRL0);
}
