blake256_final_h(state *S, uint8_t *digest, uint8_t pa, uint8_t pb) {
    uint8_t msglen[8];
    uint32_t lo = S->t[0] + S->buflen, hi = S->t[1];
    if (lo < (unsigned) S->buflen) hi++;
    U32TO8(msglen + 0, hi);
    U32TO8(msglen + 4, lo);

    if (S->buflen == 440) {
        S->t[0] -= 8;
        blake256_update(S, &pa, 8);
    } else {
        if (S->buflen < 440) {
            if (S->buflen == 0) S->nullt = 1;
            S->t[0] -= 440 - S->buflen;
            blake256_update(S, padding, 440 - S->buflen);
        } else {
            S->t[0] -= 512 - S->buflen;
            blake256_update(S, padding, 512 - S->buflen);
            S->t[0] -= 440;
            blake256_update(S, padding + 1, 440);
            S->nullt = 1;
        }
        blake256_update(S, &pb, 8);
        S->t[0] -= 8;
    }
    S->t[0] -= 64;
    blake256_update(S, msglen, 64);

    U32TO8(digest +  0, S->h[0]);
    U32TO8(digest +  4, S->h[1]);
    U32TO8(digest +  8, S->h[2]);
    U32TO8(digest + 12, S->h[3]);
    U32TO8(digest + 16, S->h[4]);
    U32TO8(digest + 20, S->h[5]);
    U32TO8(digest + 24, S->h[6]);
    U32TO8(digest + 28, S->h[7]);
}
