hashStream(hsStream* S) {
    plMD5 ctx;
    size_t size = S->size();
    unsigned char buf[64];

    size_t pos = 0;
    while (pos + 64 <= size) {
        S->read(64, buf);
        ctx.processBlock(buf);
        pos += 64;
    }


    size_t lastSize = size - pos;
    S->read(lastSize, buf);

    if (lastSize >= 56) {
        memcpy(buf + lastSize, kPadArray, 64 - lastSize);
        ctx.processBlock(buf);
        memset(buf, 0, sizeof(buf));
    } else {
        unsigned int padBytes = 56 - lastSize;
        memcpy(buf + lastSize, kPadArray, padBytes);
    }

    unsigned int bitSize[2];
    bitSize[0] = LESWAP32((size <<  3));
    bitSize[1] = LESWAP32((size >> 29));
    memcpy(buf + 56, bitSize, sizeof(bitSize));

    ctx.processBlock(buf);
    plMD5Hash hash;
    hash.fHash[0] = ctx.fA;
    hash.fHash[1] = ctx.fB;
    hash.fHash[2] = ctx.fC;
    hash.fHash[3] = ctx.fD;
    return hash;
}
