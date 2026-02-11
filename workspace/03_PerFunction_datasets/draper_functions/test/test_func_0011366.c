md5_hash(fingerprint_ty *p, unsigned char *digest)
{
    md5_ty	    *context;
    unsigned char   bits[8];
    unsigned int    idx;
    unsigned int    padLen;


    context = (md5_ty *)p;
    Encode(bits, context->count, 8);


    idx = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (idx < 56) ? (56 - idx) : (120 - idx);
    md5_addn(p, PADDING, padLen);


    md5_addn(p, bits, 8);


    Encode(digest, context->state, 16);


    reset(context);


    return MD5_HASH_LEN;
}
