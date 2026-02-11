putMark(int n)
{

	if (segUsed == segSize)
	{
		size_t newSize = segSize * 2 + 5;
		int *newMark = new int[newSize];
		memcpy(newMark, segMark, segSize * sizeof(int));
		delete segMark;
		segMark = newMark;
		segSize = newSize;
	}
	segMark[segUsed++] = n;
}
