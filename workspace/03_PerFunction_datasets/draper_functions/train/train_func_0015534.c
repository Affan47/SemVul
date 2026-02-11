GetLength()
{
	FUAssert(IsOpen(), return 0);

	size_t currentPosition = (size_t) ftell(filePtr);
	if (fseek(filePtr, 0, SEEK_END) != 0) return 0;

	size_t length = (size_t) ftell(filePtr);
	if (fseek(filePtr, (long) currentPosition, SEEK_SET) != 0) return 0;

	return length;
}
