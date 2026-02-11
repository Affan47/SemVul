NewAESCipher( const Interface &iface, int keyLen )
{
    if( keyLen <= 0 )
	keyLen = 192;

    keyLen = AESKeyRange.closest( keyLen );

    const EVP_CIPHER *blockCipher = 0;
    const EVP_CIPHER *streamCipher = 0;

    switch(keyLen)
    {
    case 128:
	blockCipher = EVP_aes_128_cbc();
	streamCipher = EVP_aes_128_cfb();
	break;

    case 192:
	blockCipher = EVP_aes_192_cbc();
	streamCipher = EVP_aes_192_cfb();
	break;

    case 256:
    default:
	blockCipher = EVP_aes_256_cbc();
	streamCipher = EVP_aes_256_cfb();
	break;
    }

    return shared_ptr<Cipher>( new SSL_Cipher(iface, AESInterface,
		blockCipher, streamCipher, keyLen / 8) );
}
