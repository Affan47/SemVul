mng_GetChunckType(const BYTE *mChunkName) {
	if(memcmp(mChunkName, mng_MHDR, 4) == 0) {
		return MHDR;
	}
	if(memcmp(mChunkName, mng_LOOP, 4) == 0) {
		return LOOP;
	}
	if(memcmp(mChunkName, mng_DEFI, 4) == 0) {
		return DEFI;
	}
	if(memcmp(mChunkName, mng_PLTE, 4) == 0) {
		return PLTE;
	}
	if(memcmp(mChunkName, mng_tRNS, 4) == 0) {
		return tRNS;
	}
	if(memcmp(mChunkName, mng_IHDR, 4) == 0) {
		return IHDR;
	}
	if(memcmp(mChunkName, mng_JHDR, 4) == 0) {
		return JHDR;
	}
	if(memcmp(mChunkName, mng_MEND, 4) == 0) {
		return MEND;
	}
	if(memcmp(mChunkName, mng_IEND, 4) == 0) {
		return IEND;
	}
	if(memcmp(mChunkName, mng_JDAT, 4) == 0) {
		return JDAT;
	}
	if(memcmp(mChunkName, mng_IDAT, 4) == 0) {
		return IDAT;
	}
	if(memcmp(mChunkName, mng_JDAA, 4) == 0) {
		return JDAA;
	}
	if(memcmp(mChunkName, mng_gAMA, 4) == 0) {
		return gAMA;
	}
	if(memcmp(mChunkName, mng_pHYs, 4) == 0) {
		return pHYs;
	}
	if(memcmp(mChunkName, mng_bKGD, 4) == 0) {
		return bKGD;
	}
	if(memcmp(mChunkName, mng_tEXt, 4) == 0) {
		return tEXt;
	}

	return UNKNOWN_CHUNCK;
}
