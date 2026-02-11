RawSetKey(CipherDir dir, const byte *key)
{
	SecByteBlock buffer(56+56+8);
	byte *const pc1m=buffer;
	byte *const pcr=pc1m+56;
	byte *const ks=pcr+56;
	register int i,j,l;
	int m;

	for (j=0; j<56; j++) {
		l=pc1[j]-1;
		m = l & 07;
		pc1m[j]=(key[l>>3] &
			bytebit[m])
			? 1 : 0;
	}
	for (i=0; i<16; i++) {
		memset(ks,0,8);
		for (j=0; j<56; j++)
			pcr[j] = pc1m[(l=j+totrot[i])<(j<28? 28 : 56) ? l: l-28];

		for (j=0; j<48; j++){

			if (pcr[pc2[j]-1]){

				l= j % 6;
				ks[j/6] |= bytebit[l] >> 2;
			}
		}

		k[2*i] = ((word32)ks[0] << 24)
			| ((word32)ks[2] << 16)
			| ((word32)ks[4] << 8)
			| ((word32)ks[6]);
		k[2*i+1] = ((word32)ks[1] << 24)
			| ((word32)ks[3] << 16)
			| ((word32)ks[5] << 8)
			| ((word32)ks[7]);
	}

	if (dir==DECRYPTION)
		for (i=0; i<16; i+=2)
		{
			std::swap(k[i], k[32-2-i]);
			std::swap(k[i+1], k[32-1-i]);
		}
}
