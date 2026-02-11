navSetHoldAlt(float alt, uint8_t relative) {
	if (relative) {
		navData.holdAlt += alt;
	} else {
		navData.holdAlt = alt;
	}
}
