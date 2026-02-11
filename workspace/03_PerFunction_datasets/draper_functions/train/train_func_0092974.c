escrypt_gensalt_r(uint32_t N_log2, uint32_t r, uint32_t p,
                  const uint8_t * src, size_t srclen,
                  uint8_t * buf, size_t buflen)
{
    uint8_t *dst;
    size_t   prefixlen =
        (sizeof "$7$" - 1U) + (1U ) + (5U ) + (5U );
    size_t   saltlen = BYTES2CHARS(srclen);
    size_t   need;

    need = prefixlen + saltlen + 1;
    if (need > buflen || need < saltlen || saltlen < srclen) {
        return NULL;
    }
    if (N_log2 > 63 || ((uint64_t)r * (uint64_t)p >= (1U << 30))) {
        return NULL;
    }
    dst = buf;
    *dst++ = '$';
    *dst++ = '7';
    *dst++ = '$';

    *dst++ = itoa64[N_log2];

    dst = encode64_uint32(dst, buflen - (dst - buf), r, 30);
    if (!dst) {
        return NULL;
    }
    dst = encode64_uint32(dst, buflen - (dst - buf), p, 30);
    if (!dst) {
        return NULL;
    }
    dst = encode64(dst, buflen - (dst - buf), src, srclen);
    if (!dst || dst >= buf + buflen) {
        return NULL;
    }
    *dst = 0;

    return buf;
}
