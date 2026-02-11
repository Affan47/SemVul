sha1_process(struct sha1_state *sha1,
                  const unsigned char *in, Py_ssize_t inlen)
{
    Py_ssize_t n;

    assert(sha1 != NULL);
    assert(in != NULL);
    assert(sha1->curlen <= sizeof(sha1->buf));

    while (inlen > 0) {
        if (sha1->curlen == 0 && inlen >= SHA1_BLOCKSIZE) {
           sha1_compress(sha1, (unsigned char *)in);
           sha1->length   += SHA1_BLOCKSIZE * 8;
           in             += SHA1_BLOCKSIZE;
           inlen          -= SHA1_BLOCKSIZE;
        } else {
           n = Py_MIN(inlen, (Py_ssize_t)(SHA1_BLOCKSIZE - sha1->curlen));
           memcpy(sha1->buf + sha1->curlen, in, (size_t)n);
           sha1->curlen   += (SHA1_INT32)n;
           in             += n;
           inlen          -= n;
           if (sha1->curlen == SHA1_BLOCKSIZE) {
              sha1_compress(sha1, sha1->buf);
              sha1->length += 8*SHA1_BLOCKSIZE;
              sha1->curlen = 0;
           }
       }
    }
}
