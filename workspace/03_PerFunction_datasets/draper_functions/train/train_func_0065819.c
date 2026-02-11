GetCipherPtr(VALUE obj)
{
    EVP_CIPHER_CTX *ctx;

    SafeGetCipher(obj, ctx);

    return EVP_CIPHER_CTX_cipher(ctx);
}
