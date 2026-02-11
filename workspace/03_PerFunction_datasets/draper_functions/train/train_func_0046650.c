ExpandKey(uchar *key, uchar *expkey){
	uchar tmp0, tmp1, tmp2, tmp3, tmp4;
	unsigned idx;

	for(idx=0; idx<Nk; idx++){
		expkey[4*idx+0] = key[4 * idx + 0];
		expkey[4*idx+1] = key[4 * idx + 1];
		expkey[4*idx+2] = key[4 * idx + 2];
		expkey[4*idx+3] = key[4 * idx + 3];
	}

	for(idx=Nk; idx<Nb*(Nr+1); idx++){
		tmp0 = expkey[4*idx - 4];
		tmp1 = expkey[4*idx - 3];
		tmp2 = expkey[4*idx - 2];
		tmp3 = expkey[4*idx - 1];
		if(!(idx%Nk)){
			tmp4 = tmp3;
			tmp3 = Sbox[tmp0];
			tmp0 = Sbox[tmp1] ^ Rcon[idx/Nk];
			tmp1 = Sbox[tmp2];
			tmp2 = Sbox[tmp4];
		}


		expkey[4*idx+0] = expkey[4*idx - 4*Nk + 0] ^ tmp0;
		expkey[4*idx+1] = expkey[4*idx - 4*Nk + 1] ^ tmp1;
		expkey[4*idx+2] = expkey[4*idx - 4*Nk + 2] ^ tmp2;
		expkey[4*idx+3] = expkey[4*idx - 4*Nk + 3] ^ tmp3;
	}
}
