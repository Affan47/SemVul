hx509_crypto_set_key_data(hx509_crypto crypto, const void *data, size_t length)
{
    if (EVP_CIPHER_key_length(crypto->c) > (int)length)
	return HX509_CRYPTO_INTERNAL_ERROR;

    if (crypto->key.data) {
	free(crypto->key.data);
	crypto->key.data = NULL;
	crypto->key.length = 0;
    }
    crypto->key.data = malloc(length);
    if (crypto->key.data == NULL)
	return ENOMEM;
    memcpy(crypto->key.data, data, length);
    crypto->key.length = length;

    return 0;
}
