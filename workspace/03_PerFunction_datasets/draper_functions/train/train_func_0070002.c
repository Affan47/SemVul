TestAsymmetricCipher(TestData &v)
{
	std::string name = GetRequiredDatum(v, "Name");
	std::string test = GetRequiredDatum(v, "Test");

	std::auto_ptr<PK_Encryptor> encryptor(ObjectFactoryRegistry<PK_Encryptor>::Registry().CreateObject(name.c_str()));
	std::auto_ptr<PK_Decryptor> decryptor(ObjectFactoryRegistry<PK_Decryptor>::Registry().CreateObject(name.c_str()));

	std::string keyFormat = GetRequiredDatum(v, "KeyFormat");

	if (keyFormat == "DER")
	{
		decryptor->AccessMaterial().Load(StringStore(GetDecodedDatum(v, "PrivateKey")).Ref());
		encryptor->AccessMaterial().Load(StringStore(GetDecodedDatum(v, "PublicKey")).Ref());
	}
	else if (keyFormat == "Component")
	{
		TestDataNameValuePairs pairs(v);
		decryptor->AccessMaterial().AssignFrom(pairs);
		encryptor->AccessMaterial().AssignFrom(pairs);
	}

	if (test == "DecryptMatch")
	{
		std::string decrypted, expected = GetDecodedDatum(v, "Plaintext");
		StringSource ss(GetDecodedDatum(v, "Ciphertext"), true, new PK_DecryptorFilter(GlobalRNG(), *decryptor, new StringSink(decrypted)));
		if (decrypted != expected)
			SignalTestFailure();
	}
	else if (test == "KeyPairValidAndConsistent")
	{
		TestKeyPairValidAndConsistent(encryptor->AccessMaterial(), decryptor->GetMaterial());
	}
	else
	{
		SignalTestError();
		assert(false);
	}
}
