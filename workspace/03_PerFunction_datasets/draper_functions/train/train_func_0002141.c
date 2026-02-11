ForwardDNAOccCount(const unsigned int*  dna, const unsigned int index, const unsigned int character,
									   const unsigned int*  dnaDecodeTable)
{
	static const unsigned int truncateRightMask[16] = { 0x00000000, 0xC0000000, 0xF0000000, 0xFC000000,
											   0xFF000000, 0xFFC00000, 0xFFF00000, 0xFFFC0000,
											   0xFFFF0000, 0xFFFFC000, 0xFFFFF000, 0xFFFFFC00,
											   0xFFFFFF00, 0xFFFFFFC0, 0xFFFFFFF0, 0xFFFFFFFC };

	unsigned int wordToCount, charToCount;
	unsigned int i, c;
	unsigned int sum = 0;

	wordToCount = index / 16;
	charToCount = index - wordToCount * 16;

	for (i=0; i<wordToCount; i++) {
		sum += dnaDecodeTable[dna[i] >> 16];
		sum += dnaDecodeTable[dna[i] & 0x0000FFFF];
	}

	if (charToCount > 0) {
		c = dna[i] & truncateRightMask[charToCount];
		sum += dnaDecodeTable[c >> 16];
		sum += dnaDecodeTable[c & 0xFFFF];
		sum += charToCount - 16;
	}

	return (sum >> (character * 8)) & 0x000000FF;

}
