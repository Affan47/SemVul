getUTF8CharPos(const XMLByte* srcBegin, const XMLByte* srcEnd, size_t bytePos){
	size_t charPos=0;
	const XMLByte* ptr=srcBegin;
	const XMLByte* ptrEnd=srcBegin+bytePos;
	while(skipUTF8Char(ptr, srcEnd)){
		if(ptr>ptrEnd)
			return charPos;
		charPos++;
	}


	throw Exception(0,
					0,
					"Error convertion byte pos to char pos");
}
