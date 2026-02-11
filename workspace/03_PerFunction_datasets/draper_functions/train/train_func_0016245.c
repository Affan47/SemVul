ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const
{
	word32 text[4], temp[4];
	Block::Get(inBlock)(text[0])(text[1])(text[2])(text[3]);


	text[0] ^= roundkeys(0, 0);
	text[1] ^= roundkeys(0, 1);
	text[2] ^= roundkeys(0, 2);
	text[3] ^= roundkeys(0, 3);


	for (int i=1; i+1<ROUNDS; i+=2)
	{
		squareRound (text, temp, Td[0], Td[1], Td[2], Td[3], roundkeys4(i));
		squareRound (temp, text, Td[0], Td[1], Td[2], Td[3], roundkeys4(i+1));
	}
	squareRound (text, temp, Td[0], Td[1], Td[2], Td[3], roundkeys4(ROUNDS-1));


	squareFinal (text, temp, Sd, roundkeys4(ROUNDS));

	Block::Put(xorBlock, outBlock)(text[0])(text[1])(text[2])(text[3]);
}
