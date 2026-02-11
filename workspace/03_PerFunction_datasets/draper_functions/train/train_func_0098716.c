ID3v2_TestFrameID_NonConformance(char* frameid) {
	for (uint8_t i=0; i < 4; i++) {
		if ( !((frameid[i] >= '0' && frameid[i] <= '9') || ( frameid[i] >= 'A' && frameid[i] <= 'Z' )) ) {
			return true;
		}
	}
	return false;
}
