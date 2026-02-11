RsaUnPad(const byte *pkcsBlock, unsigned int pkcsBlockLen,
                       byte **output, byte padValue)
{
    word32 maxOutputLen = (pkcsBlockLen > 10) ? (pkcsBlockLen - 10) : 0,
           invalid = 0,
           i = 1,
           outputLen;

    if (pkcsBlock[0] != 0x0)
        invalid = 1;
    pkcsBlock++; pkcsBlockLen--;


    invalid = (pkcsBlock[0] != padValue) || invalid;


    while (i<pkcsBlockLen && pkcsBlock[i++]) {
        }
    if(!(i==pkcsBlockLen || pkcsBlock[i-1]==0)) {
        CYASSL_MSG("RsaUnPad error, bad formatting");
        return 0;
    }

    outputLen = pkcsBlockLen - i;
    invalid = (outputLen > maxOutputLen) || invalid;

    if (invalid) {
        CYASSL_MSG("RsaUnPad error, bad formatting");
        return 0;
    }

    *output = (byte *)(pkcsBlock + i);
    return outputLen;
}
