DoNamcoSoundHQ(void) {
	int32 P, V;
	int32 cyclesuck = (((IRAM[0x7F] >> 4) & 7) + 1) * 15;

	for (P = 7; P >= (7 - ((IRAM[0x7F] >> 4) & 7)); P--) {
		if ((IRAM[0x44 + (P << 3)] & 0xE0) && (IRAM[0x47 + (P << 3)] & 0xF)) {
			uint32 freq;
			int32 vco;
			uint32 duff2, lengo, envelope;

			vco = vcount[P];
			freq = FreqCache[P];
			envelope = EnvCache[P];
			lengo = LengthCache[P];

			duff2 = FetchDuff(P, envelope);
			for (V = CVBC << 1; V < (int)SOUNDTS << 1; V++) {
				WaveHi[V >> 1] += duff2;
				if (!vco) {
					PlayIndex[P] += freq;
					while ((PlayIndex[P] >> TOINDEX) >= lengo) PlayIndex[P] -= lengo << TOINDEX;
					duff2 = FetchDuff(P, envelope);
					vco = cyclesuck;
				}
				vco--;
			}
			vcount[P] = vco;
		}
	}
	CVBC = SOUNDTS;
}
