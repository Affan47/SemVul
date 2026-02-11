Encrypt(byte *Key, unsigned kbytes, byte *N, unsigned nbytes, byte *AD,
        unsigned adbytes, byte *M, unsigned mbytes, unsigned abytes, byte *C) {
    byte K[16], buf[16], *T, *X;
    unsigned tbytes;
    ExtractKey(Key, kbytes, K);
    X = (byte *)malloc(mbytes+abytes);
    memcpy(X, M, mbytes); memset(X+mbytes,0,abytes);
    Format(N, nbytes, AD, adbytes, abytes, &T, &tbytes);
    if (mbytes==0) {
        AMAC(K, T, tbytes, 4, buf);
        memcpy(C,buf,abytes);
    } else
        Cipher(K, T, tbytes, X, mbytes+abytes, 0, C);
    free(T);
    free(X);
}
