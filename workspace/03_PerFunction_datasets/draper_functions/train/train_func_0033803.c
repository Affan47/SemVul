RsaPad(const byte* input, word32 inputLen, byte* pkcsBlock,
                   word32 pkcsBlockLen, byte padValue, RNG* rng)
{
    if (inputLen == 0) return;

    pkcsBlock[0] = 0x0;
    pkcsBlock++; pkcsBlockLen--;
    pkcsBlock[0] = padValue;

    if (padValue == RSA_BLOCK_TYPE_1)

        XMEMSET(&pkcsBlock[1], 0xFF, pkcsBlockLen - inputLen - 2);
    else {

        word32 padLen = pkcsBlockLen - inputLen - 1, i;
        RNG_GenerateBlock(rng, &pkcsBlock[1], padLen);


        for (i = 1; i < padLen; i++)
            if (pkcsBlock[i] == 0) pkcsBlock[i] = 0x01;
    }

    pkcsBlock[pkcsBlockLen-inputLen-1] = 0;
    XMEMCPY(pkcsBlock+pkcsBlockLen-inputLen, input, inputLen);
}
