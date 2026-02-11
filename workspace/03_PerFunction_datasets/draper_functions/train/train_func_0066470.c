index_to_tokens (uint32_t index, char* buf) {
    for (uint32_t i = 0; i < APPEARS_SEQSIZE; i++) {
        uint32_t encoded_token =
            (index >> (i * BITS_PER_TOKEN)) & 3L;
        switch (encoded_token) {
            case G:
                buf[APPEARS_SEQSIZE - i - 1] = 'G';
                break;
            case A:
                buf[APPEARS_SEQSIZE - i - 1] = 'A';
                break;
            case T:
                buf[APPEARS_SEQSIZE - i - 1] = 'T';
                break;
            case C:
                buf[APPEARS_SEQSIZE - i - 1] = 'C';
                break;
            default:
                break;
        }
    }
    buf[APPEARS_SEQSIZE] = '\0';

}
