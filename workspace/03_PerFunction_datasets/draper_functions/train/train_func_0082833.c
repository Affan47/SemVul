digest()
{
	int count;
	UInt32 lowBitcount  = _context.countLo;
	UInt32 highBitcount = _context.countHi;


	count = (int) ((_context.countLo >> 3) & 0x3F);


	((BYTE*) _context.data)[count++] = 0x80;


	if (count > 56)
	{

		std::memset((BYTE*) &_context.data + count, 0, 64 - count);
		SHA1_BYTE_REVERSE(_context.data, BLOCK_SIZE);
		transform();


		std::memset(&_context.data, 0, 56);
	}
	else
	{

		std::memset((BYTE*) &_context.data + count, 0, 56 - count);
	}
	SHA1_BYTE_REVERSE(_context.data, BLOCK_SIZE);


	_context.data[14] = highBitcount;
	_context.data[15] = lowBitcount;

	transform();
	SHA1_BYTE_REVERSE(_context.data, DIGEST_SIZE);

	unsigned char hash[DIGEST_SIZE];
	for (count = 0; count < DIGEST_SIZE; count++)
		hash[count] = (BYTE) ((_context.digest[count>>2]) >> (8*(3-(count & 0x3)))) & 0xff;
	_digest.clear();
	_digest.insert(_digest.begin(), hash, hash + DIGEST_SIZE);
	reset();
	return _digest;
}
