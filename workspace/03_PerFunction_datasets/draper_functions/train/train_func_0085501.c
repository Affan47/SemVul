rotate(uint64_t prekey, int a, int b) {
    if(prekey & ((uint64_t) 1 << a)) {
        prekey |= ((uint64_t) 1 << b);
        prekey ^= ((uint64_t) 1 << a);
    }
    return prekey;
}
