grow(lenpos_t lenNew) {
	while (sizeGrowth * 6 < lenNew) {
		sizeGrowth *= 2;
	}
	char *sNew = new char[lenNew + sizeGrowth + 1];
	if (sNew) {
		if (s) {
			memcpy(sNew, s, sLen);
			delete []s;
		}
		s = sNew;
		s[sLen] = '\0';
		sSize = lenNew + sizeGrowth;
	}
	return sNew != 0;
}
