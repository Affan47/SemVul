Flush()
{
	FUAssert(IsOpen(),);
	fflush(filePtr);
}
