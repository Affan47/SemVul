TestModeIV(SymmetricCipher &e, SymmetricCipher &d)
{
	SecByteBlock lastIV, iv(e.IVSize());
	StreamTransformationFilter filter(e, new StreamTransformationFilter(d));
	byte plaintext[20480];

	for (unsigned int i=1; i<sizeof(plaintext); i*=2)
	{
		e.GetNextIV(GlobalRNG(), iv);
		if (iv == lastIV)
			return false;
		else
			lastIV = iv;

		e.Resynchronize(iv);
		d.Resynchronize(iv);

		unsigned int length = STDMAX(GlobalRNG().GenerateWord32(0, i), (word32)e.MinLastBlockSize());
		GlobalRNG().GenerateBlock(plaintext, length);

		if (!TestFilter(filter, plaintext, length, plaintext, length))
			return false;
	}

	return true;
}
