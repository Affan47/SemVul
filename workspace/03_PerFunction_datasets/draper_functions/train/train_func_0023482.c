M49PW(uint32 A, uint8 V) {
	if (EXPREGS[0] & 1) {
		V &= 0xF;
		V |= (EXPREGS[0] & 0xC0) >> 2;
		setprg8(A, V);
	} else
		setprg32(0x8000, (EXPREGS[0] >> 4) & 3);
}
