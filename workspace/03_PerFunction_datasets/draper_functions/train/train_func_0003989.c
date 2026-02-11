artemia_permutation(unsigned char *X,
                         unsigned char *Y)
{
    int round, i;

    memcpy(Y, X, 2 * BLOCK_BYTE_SIZE * sizeof(unsigned char));

    for(round = 0 ; round < 6 ; round++){

        for(i=0 ; i < 2*BLOCK_BYTE_SIZE ; i++)
            Y[i] ^= C[round][i];


        transformation_D1(Y, Y+8, Y+16, Y+24);


        for(i=0 ; i < 2*BLOCK_BYTE_SIZE ; i++)
            Y[i] = AES_SBOX[Y[i]];


        transformation_D2(Y, Y+2, Y+4, Y+6);
        transformation_D2(Y+8, Y+10, Y+12, Y+14);
        transformation_D2(Y+16, Y+18, Y+20, Y+22);
        transformation_D2(Y+24, Y+26, Y+28, Y+30);


        for(i=0 ; i < 2*BLOCK_BYTE_SIZE ; i++)
            Y[i] = AES_SBOX[Y[i]];


        for(i=0 ; i<2*BLOCK_BYTE_SIZE ; i+=2)
            transformation_D3(Y+i, Y+i+1);


        for(i=0 ; i < 2*BLOCK_BYTE_SIZE ; i++)
            Y[i] = AES_SBOX[Y[i]];
    }
}
