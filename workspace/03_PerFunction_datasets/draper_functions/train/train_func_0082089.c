escrypt_r(escrypt_local_t * local, const uint8_t * passwd, size_t passwdlen,
          const uint8_t * setting, uint8_t * buf, size_t buflen)
{
    uint8_t        hash[crypto_pwhash_scryptsalsa208sha256_STRHASHBYTES];
    escrypt_kdf_t  escrypt_kdf;
    const uint8_t *src;
    const uint8_t *salt;
    uint8_t       *dst;
    size_t         prefixlen;
    size_t         saltlen;
    size_t         need;
    uint64_t       N;
    uint32_t       N_log2;
    uint32_t       r;
    uint32_t       p;

    if (setting[0] != '$' || setting[1] != '7' || setting[2] != '$') {
        return NULL;
    }
    src = setting + 3;

    if (decode64_one(&N_log2, *src)) {
        return NULL;
    }
    src++;
    N = (uint64_t)1 << N_log2;

    src = decode64_uint32(&r, 30, src);
    if (!src) {
        return NULL;
    }
    src = decode64_uint32(&p, 30, src);
    if (!src) {
        return NULL;
    }
    prefixlen = src - setting;

    salt = src;
    src = (uint8_t *) strrchr((char *)salt, '$');
    if (src) {
        saltlen = src - salt;
    } else {
        saltlen = strlen((char *)salt);
    }
    need = prefixlen + saltlen + 1 +
        crypto_pwhash_scryptsalsa208sha256_STRHASHBYTES_ENCODED + 1;
    if (need > buflen || need < saltlen) {
        return NULL;
    }
#if defined(HAVE_EMMINTRIN_H) || defined(_MSC_VER)
    escrypt_kdf =
        sodium_runtime_has_sse2() ? escrypt_kdf_sse : escrypt_kdf_nosse;
#else
    escrypt_kdf = escrypt_kdf_nosse;
#endif
    if (escrypt_kdf(local, passwd, passwdlen, salt, saltlen,
                    N, r, p, hash, sizeof(hash))) {
        return NULL;
    }

    dst = buf;
    memcpy(dst, setting, prefixlen + saltlen);
    dst += prefixlen + saltlen;
    *dst++ = '$';

    dst = encode64(dst, buflen - (dst - buf), hash, sizeof(hash));
    sodium_memzero(hash, sizeof hash);
    if (!dst || dst >= buf + buflen) {
        return NULL;
    }
    *dst = 0;

    return buf;
}
