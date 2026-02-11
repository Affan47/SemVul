generate_key(const char *file)
{
    EVP_PKEY* pkey = EVP_PKEY_new();
    BIGNUM* exponent = BN_new();
    RSA* rsa = RSA_new();
    mode_t old_mask;
    FILE *f = NULL;
    int ret = 0;

    D("generate_key '%s'\n", file);

    if (!pkey || !exponent || !rsa) {
        D("Failed to allocate key\n");
        goto out;
    }

    BN_set_word(exponent, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, exponent, NULL);
    EVP_PKEY_set1_RSA(pkey, rsa);

    old_mask = umask(077);

    f = fopen(file, "w");
    if (!f) {
        D("Failed to open '%s'\n", file);
        umask(old_mask);
        goto out;
    }

    umask(old_mask);

    if (!PEM_write_PrivateKey(f, pkey, NULL, NULL, 0, NULL, NULL)) {
        D("Failed to write key\n");
        goto out;
    }

    if (!write_public_keyfile(rsa, file)) {
        D("Failed to write public key\n");
        goto out;
    }

    ret = 1;

out:
    if (f)
        fclose(f);
    EVP_PKEY_free(pkey);
    RSA_free(rsa);
    BN_free(exponent);
    return ret;
}
