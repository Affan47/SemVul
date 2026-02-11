generator_output(struct fortuna_state *st, unsigned char *dst, size_t len)
{
    unsigned char result[AES256_BLOCKSIZE];
    size_t n, count = 0;

    while (len > 0) {

        encrypt_counter(st, result);
        n = (len < AES256_BLOCKSIZE) ? len : AES256_BLOCKSIZE;
        memcpy(dst, result, n);
        dst += n;
        len -= n;


        count += AES256_BLOCKSIZE;
        if (count >= MAX_BYTES_PER_KEY) {
            change_key(st);
            count = 0;
        }
    }
    zap(result, sizeof(result));


    change_key(st);
}
