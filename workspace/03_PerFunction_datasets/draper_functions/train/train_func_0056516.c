scanhash_cryptonight(int thr_id, uint32_t *pdata, const uint32_t *ptarget,
        uint32_t max_nonce, unsigned long *hashes_done) {
    uint32_t *nonceptr = (uint32_t*) (((char*)pdata) + 39);
    uint32_t n = *nonceptr - 1;
    const uint32_t first_nonce = n + 1;
    const uint32_t Htarg = ptarget[7];
    uint32_t hash[HASH_SIZE / 4] __attribute__((aligned(32)));

    struct cryptonight_ctx *ctx = alloca(sizeof(struct cryptonight_ctx));

    do {
        *nonceptr = ++n;
        cryptonight_hash_ctx(hash, pdata, 76, ctx);
        if (unlikely(hash[7] < ptarget[7])) {
            *hashes_done = n - first_nonce + 1;
            return true;
        }
    } while (likely((n <= max_nonce && !work_restart[thr_id].restart)));
    *hashes_done = n - first_nonce + 1;
    return 0;
}
