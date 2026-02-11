ValidateSHACAL2()
{
	cout << "\nSHACAL-2 validation suite running...\n\n";

	bool pass = true;
	FileSource valdata(PACKAGE_DATA_DIR "TestData/shacal2v.dat", true, new HexDecoder);
	pass = BlockTransformationTest(FixedRoundsCipherFactory<SHACAL2Encryption, SHACAL2Decryption>(16), valdata, 4) && pass;
	pass = BlockTransformationTest(FixedRoundsCipherFactory<SHACAL2Encryption, SHACAL2Decryption>(64), valdata, 10) && pass;
	return pass;
}
