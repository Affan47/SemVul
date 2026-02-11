FirstPut(const byte *)
{

	CRYPTOPP_COMPILE_ASSERT_INSTANCE(SALTLENGTH <= DefaultHashModule::DIGESTSIZE, 1);
	CRYPTOPP_COMPILE_ASSERT_INSTANCE(BLOCKSIZE <= DefaultHashModule::DIGESTSIZE, 2);

	SecByteBlock salt(DefaultHashModule::DIGESTSIZE), keyCheck(DefaultHashModule::DIGESTSIZE);
	DefaultHashModule hash;


	hash.Update(m_passphrase, m_passphrase.size());
	time_t t=time(0);
	hash.Update((byte *)&t, sizeof(t));
	clock_t c=clock();
	hash.Update((byte *)&c, sizeof(c));
	hash.Final(salt);


	hash.Update(m_passphrase, m_passphrase.size());
	hash.Update(salt, SALTLENGTH);
	hash.Final(keyCheck);

	AttachedTransformation()->Put(salt, SALTLENGTH);


	SecByteBlock key(KEYLENGTH);
	SecByteBlock IV(BLOCKSIZE);
	GenerateKeyIV(m_passphrase, m_passphrase.size(), salt, SALTLENGTH, key, IV);

	m_cipher.SetKeyWithIV(key, key.size(), IV);
	SetFilter(new StreamTransformationFilter(m_cipher));

	m_filter->Put(keyCheck, BLOCKSIZE);
}
