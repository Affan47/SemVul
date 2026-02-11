BenchMarkAgreement(const char *name, AuthenticatedKeyAgreementDomain &d, double timeTotal, bool pc=false)
{
	SecByteBlock spriv1(d.StaticPrivateKeyLength()), spriv2(d.StaticPrivateKeyLength());
	SecByteBlock epriv1(d.EphemeralPrivateKeyLength()), epriv2(d.EphemeralPrivateKeyLength());
	SecByteBlock spub1(d.StaticPublicKeyLength()), spub2(d.StaticPublicKeyLength());
	SecByteBlock epub1(d.EphemeralPublicKeyLength()), epub2(d.EphemeralPublicKeyLength());
	d.GenerateStaticKeyPair(GlobalRNG(), spriv1, spub1);
	d.GenerateStaticKeyPair(GlobalRNG(), spriv2, spub2);
	d.GenerateEphemeralKeyPair(GlobalRNG(), epriv1, epub1);
	d.GenerateEphemeralKeyPair(GlobalRNG(), epriv2, epub2);
	SecByteBlock val(d.AgreedValueLength());

	clock_t start = clock();
	unsigned int i;
	double timeTaken;
	for (timeTaken=(double)0, i=0; timeTaken < timeTotal; timeTaken = double(clock() - start) / CLOCK_TICKS_PER_SECOND, i+=2)
	{
		d.Agree(val, spriv1, epriv1, spub2, epub2);
		d.Agree(val, spriv2, epriv2, spub1, epub1);
	}

	OutputResultOperations(name, "Key Agreement", pc, i, timeTaken);
}
