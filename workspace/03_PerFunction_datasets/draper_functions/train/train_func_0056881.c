IsSmallPrime(const Integer &p)
{
	unsigned int primeTableSize;
	const word16 * primeTable = GetPrimeTable(primeTableSize);

	if (p.IsPositive() && p <= primeTable[primeTableSize-1])
		return std::binary_search(primeTable, primeTable+primeTableSize, (word16)p.ConvertToLong());
	else
		return false;
}
