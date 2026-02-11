Init(const char *const *linesForm) {
	Clear();
	height = 1;
	width = 1;
	nColours = 1;
	data = NULL;
	codeTransparent = ' ';
	codes = NULL;
	colours = NULL;
	lines = NULL;
	if (!linesForm)
		return;

	const char *line0 = linesForm[0];
	width = atoi(line0);
	line0 = NextField(line0);
	height = atoi(line0);
	line0 = NextField(line0);
	nColours = atoi(line0);
	line0 = NextField(line0);
	if (atoi(line0) != 1) {

		return;
	}
	codes = new char[nColours];
	colours = new ColourDesired[nColours];

	int strings = 1+height+nColours;
	lines = new char *[strings];
	size_t allocation = 0;
	for (int i=0; i<strings; i++) {
		allocation += MeasureLength(linesForm[i]) + 1;
	}
	data = new char[allocation];
	char *nextBit = data;
	for (int j=0; j<strings; j++) {
		lines[j] = nextBit;
		size_t len = MeasureLength(linesForm[j]);
		memcpy(nextBit, linesForm[j], len);
		nextBit += len;
		*nextBit++ = '\0';
	}

	for (int code=0; code<256; code++) {
		colourCodeTable[code] = 0;
	}

	for (int c=0; c<nColours; c++) {
		const char *colourDef = linesForm[c+1];
		codes[c] = colourDef[0];
		colourDef += 4;
		if (*colourDef == '#') {
			colours[c].Set(colourDef);
		} else {
			colours[c] = ColourDesired(0xff, 0xff, 0xff);
			codeTransparent = codes[c];
		}
		colourCodeTable[static_cast<unsigned char>(codes[c])] = &(colours[c]);
	}
}
