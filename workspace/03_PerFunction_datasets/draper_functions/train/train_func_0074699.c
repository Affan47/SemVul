g450_vco2f(unsigned char p, unsigned int fvco) {
	return (p & 0x40) ? fvco : fvco >> ((p & 3) + 1);
}
