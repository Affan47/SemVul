Reduce(Byte *Result, Chunk n, Chunk result, int length)
{
	Byte *Modulus;

	int i;
	NumCarry carryFlag = 0;
	Modulus = (Byte*) malloc((length) * sizeof(Byte));

	ConvertLongNum(n, Modulus, length);

	LongNumShiftLeftMany(Modulus, (length - SIZE) * 8, length);

	for (i = 1; i <= (length - SIZE) * 8; i++)
	{
		if (LongNumCompare(Result, Modulus, length) >= 0)
			LongNumSub(Result, Modulus, Result, &carryFlag, length);
		LongNumShiftRight(Modulus, &carryFlag, length);
	}
	if (LongNumCompare(Result, Modulus, length) >= 0)
		LongNumSub(Result, Modulus, Result, &carryFlag, length);
	NumSetEqual(Result, result);

	free(Modulus);
}
