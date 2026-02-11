OpenPGPDecode(BufferedTransformation &bt)
{
	word16 bitCount;
	if (bt.GetWord16(bitCount) != 2 || bt.MaxRetrievable() < BitsToBytes(bitCount))
		throw OpenPGPDecodeErr();
	Decode(bt, BitsToBytes(bitCount));
}
