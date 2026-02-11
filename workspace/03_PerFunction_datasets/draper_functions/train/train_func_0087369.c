rand64(tinymt64_t *state, uint64_t n) {
    uint64_t x, max = ~UINT64_C(0);
    max -= max % n;
    do {
        x = tinymt64_generate_uint64(state);
    } while (x >= max);
    return x % n;
}
