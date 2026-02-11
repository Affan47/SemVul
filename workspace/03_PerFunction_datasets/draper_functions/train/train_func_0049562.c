KeySetupEnc(u32 mk[], u32 sk[], u8 L[], u8 Lprime[], u8 keyprime[], const u32 rk[], const u8 key[]){

    u8 pt[16];
    u8 ct[16];

    int i;


    for(i=0; i<16; ++i){
        keyprime[i]=key[i]^0xF0;
    }


    memset(pt, 0x00, 16);
    aesEncrypt(rk, pt, L);


    for(i=1; i<=3*d; ++i){
        pt[15]=i;
        aesEncrypt(rk, pt, ct);

        sk[0]=GETU32(ct);
        sk[1]=GETU32(ct+4);
        sk[2]=GETU32(ct+8);
        sk[3]=GETU32(ct+12);

        sk=sk+4;
    }


    for(i=3*d+1; i<=4*d; ++i){
        pt[15]=i;

        aesEncrypt(rk, pt, ct);

        mk[0]=GETU32(ct);
        mk[1]=GETU32(ct+4);
        mk[2]=GETU32(ct+8);
        mk[3]=GETU32(ct+12);

        mk=mk+4;
    }


    memset(pt, 0xFF, 16);
    aesEncrypt(rk, pt, Lprime);
}
