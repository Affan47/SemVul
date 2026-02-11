transcodeToUTF8(const XMLByte* srcData, int& srcLen,
				XMLByte *toFill, int& toFillLen,
				const Charset::Tables& tables) {
	const XMLByte* srcPtr=srcData;
	const XMLByte* srcEnd=srcData+srcLen;
	XMLByte* outPtr=toFill;
	XMLByte* outEnd=toFill+toFillLen;

	while(srcPtr<srcEnd) {
		uint curVal = tables.fromTable[*srcPtr];
		if(!curVal) {

			*outPtr++= '?';
			srcPtr++;
			continue;
		}


		unsigned int encodedBytes;
		if(curVal<0x80)
			encodedBytes = 1;
		else if(curVal<0x800)
			encodedBytes = 2;
		else if(curVal<0x10000)
			encodedBytes = 3;
		else if(curVal<0x200000)
			encodedBytes = 4;
		else if(curVal<0x4000000)
			encodedBytes = 5;
		else if(curVal<= 0x7FFFFFFF)
			encodedBytes = 6;
		else {

			*outPtr++= '?';
			srcPtr++;
			continue;
		}


		if (outPtr + encodedBytes > outEnd)
			break;


		srcPtr++;


		outPtr+= encodedBytes;
		switch(encodedBytes) {
			case 6: *--outPtr = XMLByte((curVal | 0x80UL) & 0xBFUL);
				curVal>>= 6;
			case 5: *--outPtr = XMLByte((curVal | 0x80UL) & 0xBFUL);
				curVal>>= 6;
			case 4: *--outPtr = XMLByte((curVal | 0x80UL) & 0xBFUL);
				curVal>>= 6;
			case 3: *--outPtr = XMLByte((curVal | 0x80UL) & 0xBFUL);
				curVal>>= 6;
			case 2: *--outPtr = XMLByte((curVal | 0x80UL) & 0xBFUL);
				curVal>>= 6;
			case 1: *--outPtr = XMLByte(curVal | gFirstByteMark[encodedBytes]);
		}


		outPtr+= encodedBytes;
	}


	srcLen = srcPtr - srcData;


	toFillLen = outPtr - toFill;


	return 0;
}
