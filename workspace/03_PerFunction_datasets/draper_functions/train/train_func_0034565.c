PXMAC(const u32 mk[], const u32 sk[], const u8 L[], u8 V[], const u32 rk[], const u8 ad[], unsigned long long int adlen){

      int i=0;
      u8 pt[16], ct[16];
      u8 final_block_mask[16];


      memset(pt, 0, 16);
      memset(ct, 0, 16);


      memset(V, 0x00, 16);

      while(adlen>16){
            aesReducedEnc(mk+4*i, sk+12*i, ad, ct);
            xor_byte_string(ct, V, 16);

            ++i;
            ad+=16;
            adlen-=16;

            if(i==d){
                aesEncrypt(rk, V, ct);
                memcpy(V, ct, 16);
                i=0;
            }
      }


      memcpy(final_block_mask, L, 16);
      double_mask(final_block_mask);

      memcpy(pt, ad, adlen);

      if(adlen!=16){
            double_mask(final_block_mask);

            pt[adlen]=0x80;
            memset(pt+adlen+1, 0x00, 15-adlen);
      }

      aesReducedEnc(mk+4*i, sk+12*i, pt, ct);
      xor_byte_string(ct, V, 16);

      xor_byte_string(final_block_mask, V, 16);


      aesEncrypt(rk, V, ct);
      memcpy(V, ct, 16);

}
