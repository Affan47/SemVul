TAES_DECRYPT(const u8* in,u8* out,u8* rk,u8* counter){
	 int i;
	 u8 tempcounter;


	 for(i=0;i<16;i++){
		tempcounter =counter[i];
		rk[16+i]=rk[16*11+i]^tempcounter;
		rk[16*5+i]=rk[16*12+i]^tempcounter;
		rk[16*9+i]=rk[16*13+i]^tempcounter;
	}

 rijndaelDecrypt(rk,in,out);


}
