XEXLayerDec(const u32 irk[], const u8 Lprime[], const u8 C[], u8 Z[], unsigned long long int ctlen){

    u8 mask[16];
    u8 temp[16];
    u8 pt[16];

    memcpy(mask, Lprime, 16);

    while(ctlen!=0){
        double_mask(mask);

        memcpy(temp, C, 16);
        xor_byte_string(mask, temp, 16);
        aesDecrypt(irk, temp, pt);
        xor_byte_string(mask, pt, 16);

        memcpy(Z, pt, 16);

        C+=16;
        Z+=16;
        ctlen-=16;
    }
}
