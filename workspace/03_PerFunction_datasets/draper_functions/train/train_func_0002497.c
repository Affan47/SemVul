TAG(u8* checksum,
         u64 adlen,u64 mlen,u8* rkey,u8* tag,u8* kappa){

	u8 i;
	u8 tempkey;
	u8 tmp[16];
	u64 L=(u64)kappa[0];
	u64 R=(u64)kappa[8];
	u64 H=256;
	for(i=1;i<8;i++){
		L+=H*((u64)kappa[i]);
		R+=H*((u64)kappa[i+8]);
		H=H*256;
	}
	L+=adlen;
	R+=mlen;
	LESTOREu64inbytearray(L,tmp);
	LESTOREu64inbytearray(R,tmp+8);

	for(i=0;i<16;i++) {
		tempkey=rkey[i];
		rkey[i]=rkey[i+16*2];
		rkey[i+16*2]=rkey[i+16*3];
		rkey[i+16*3]=rkey[i+16*4];
		rkey[i+16*4]=rkey[i+16*6];
		rkey[i+16*6]=rkey[i+16*7];
		rkey[i+16*7]=rkey[i+16*8];
		rkey[i+16*8]=rkey[i+160];
		rkey[i+160]=tempkey;
		tempkey=rkey[i+16*12];


		rkey[i+16*12]=rkey[i+16*11];
		rkey[i+16*11]=rkey[i+16*13];
		rkey[i+16*13]=tempkey;
	}


         TAES_ENCRYPT(checksum,tag,rkey,(tmp));


   }
