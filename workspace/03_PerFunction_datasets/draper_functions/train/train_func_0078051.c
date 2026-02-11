findWord(const char *word) {
	long b, e;
	long m, rm;
	int comp;
	int pos;


	b = firstWordPointer;
	e = lastWordPointer;
	comp = strcmp(compBuffer, word);
	if (comp < 0) {
		b = lastSearchWordPointer;
	} else if (comp > 0) {
		e = lastSearchWordPointer;
	} else {
		currentWordPointer = lastSearchWordPointer;
		readData();
		return true;
	}


	while (true) {
		m = (b + e) / 2;
		rm = m;
		fseek(dataFile, m, SEEK_SET);
		fread(dataBuffer, 1, MAX_DATA_LEN, dataFile);
		pos = strlen(dataBuffer);
		m += pos;
		toLegalDictionaryWord(dataBuffer + pos);
		if (m == e) {
			comp = strcmp(compBuffer, word);
			if (comp <= 0) {
				break;
			} else {
				m = rm;
				fseek(dataFile, m, SEEK_SET);
				fread(dataBuffer, 1, 1, dataFile);
				while (dataBuffer[0] != DATA_SEPARATOR) {
					m--;
					fseek(dataFile, m, SEEK_SET);
					fread(dataBuffer, 1, 1, dataFile);
				}
				fread(dataBuffer, 1, MAX_WORD_LEN, dataFile);
				toLegalDictionaryWord(dataBuffer);
				if (m == b) {
					comp = strcmp(compBuffer, word);
					if (comp < 0) {
						m = e;
					}
					break;
				}
			}
		}
		comp = strcmp(compBuffer, word);
		if (comp < 0) {
			b = m;
		} else if (comp > 0) {
			e = m;
		} else {
			break;
		}
	}
	lastSearchWordPointer = m;
	currentWordPointer = m;
	readData();
	toLegalDictionaryWord(dataBuffer);
	return (comp == 0);
}
