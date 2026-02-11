decrypt(private_key_t *private, chunk_t key, chunk_t iv, int oid,
					chunk_t encrypted, chunk_t *plain)
{
	encryption_algorithm_t alg;
	chunk_t plain_key;
	crypter_t *crypter;
	size_t key_size;

	alg = encryption_algorithm_from_oid(oid, &key_size);
	if (alg == ENCR_UNDEFINED)
	{
		DBG1(DBG_LIB, "unsupported content encryption algorithm");
		return FALSE;
	}
	if (!private->decrypt(private, ENCRYPT_RSA_PKCS1, key, &plain_key))
	{
		DBG1(DBG_LIB, "symmetric key could not be decrypted with rsa");
		return FALSE;
	}
	crypter = lib->crypto->create_crypter(lib->crypto, alg, key_size / 8);
	if (!crypter)
	{
		DBG1(DBG_LIB, "crypter %N-%d not available",
			 encryption_algorithm_names, alg, key_size);
		free(plain_key.ptr);
		return FALSE;
	}
	if (plain_key.len != crypter->get_key_size(crypter))
	{
		DBG1(DBG_LIB, "symmetric key length %d is wrong", plain_key.len);
		free(plain_key.ptr);
		crypter->destroy(crypter);
		return FALSE;
	}
	if (iv.len != crypter->get_iv_size(crypter))
	{
		DBG1(DBG_LIB, "IV length %d is wrong", iv.len);
		free(plain_key.ptr);
		crypter->destroy(crypter);
		return FALSE;
	}
	if (!crypter->set_key(crypter, plain_key) ||
		!crypter->decrypt(crypter, encrypted, iv, plain))
	{
		free(plain_key.ptr);
		crypter->destroy(crypter);
		return FALSE;
	}
	DBG4(DBG_LIB, "decrypted content with padding: %B", plain);
	free(plain_key.ptr);
	crypter->destroy(crypter);
	return TRUE;
}
