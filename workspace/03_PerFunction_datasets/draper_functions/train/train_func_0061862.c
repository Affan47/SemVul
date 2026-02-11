Do5PCMHQ() {
	uint32 V;
	if (!(MMC5Sound.rawcontrol & 0x40) && MMC5Sound.raw)
		for (V = MMC5Sound.BC[2]; V < SOUNDTS; V++)
			WaveHi[V] += MMC5Sound.raw << 5;
	MMC5Sound.BC[2] = SOUNDTS;
}
