Append(const char * cStringToAppend)
	{

		uint32_t appendStringLength = strlen(cStringToAppend);


		char * newCStringPtr = new char[this->length + appendStringLength + 1];


		strncpy(newCStringPtr, this->cStr, this->length);


		strncpy(newCStringPtr + this->length, cStringToAppend, appendStringLength);


		newCStringPtr[this->length + appendStringLength] = '\0';


		delete[] this->cStr;


		this->cStr = newCStringPtr;


		this->length += appendStringLength;

	}
