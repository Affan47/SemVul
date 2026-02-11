rsa_FormatOneBlock(unsigned modulusLen,
                   RSA_BlockType blockType,
                   SECItem * data)
{
    unsigned char *block;
    unsigned char *bp;
    int padLen;
    int i, j;
    SECStatus rv;

    block = (unsigned char *) PORT_Alloc(modulusLen);
    if (block == NULL)
        return NULL;

    bp = block;


    *bp++ = RSA_BLOCK_FIRST_OCTET;
    *bp++ = (unsigned char) blockType;

    switch (blockType) {


      case RSA_BlockPrivate:


        padLen = modulusLen - data->len - 3;
        PORT_Assert(padLen >= RSA_BLOCK_MIN_PAD_LEN);
        if (padLen < RSA_BLOCK_MIN_PAD_LEN) {
            PORT_Free(block);
            return NULL;
        }
        PORT_Memset(bp, RSA_BLOCK_PRIVATE_PAD_OCTET, padLen);
        bp += padLen;
        *bp++ = RSA_BLOCK_AFTER_PAD_OCTET;
        PORT_Memcpy(bp, data->data, data->len);
        break;


      case RSA_BlockPublic:


        padLen = modulusLen - (data->len + 3);
        PORT_Assert(padLen >= RSA_BLOCK_MIN_PAD_LEN);
        if (padLen < RSA_BLOCK_MIN_PAD_LEN) {
            PORT_Free(block);
            return NULL;
        }
        j = modulusLen - 2;
        rv = RNG_GenerateGlobalRandomBytes(bp, j);
        if (rv == SECSuccess) {
            for (i = 0; i < padLen; ) {
                unsigned char repl;

                if (bp[i] != RSA_BLOCK_AFTER_PAD_OCTET) {
                    ++i;
                    continue;
                }
                if (j <= padLen) {
                    rv = RNG_GenerateGlobalRandomBytes(bp + padLen,
                                          modulusLen - (2 + padLen));
                    if (rv != SECSuccess)
                        break;
                    j = modulusLen - 2;
                }
                do {
                    repl = bp[--j];
                } while (repl == RSA_BLOCK_AFTER_PAD_OCTET && j > padLen);
                if (repl != RSA_BLOCK_AFTER_PAD_OCTET) {
                    bp[i++] = repl;
                }
            }
        }
        if (rv != SECSuccess) {
            PORT_Free(block);
            PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
            return NULL;
        }
        bp += padLen;
        *bp++ = RSA_BLOCK_AFTER_PAD_OCTET;
        PORT_Memcpy(bp, data->data, data->len);
        break;

      default:
        PORT_Assert(0);
        PORT_Free(block);
        return NULL;
    }

    return block;
}
