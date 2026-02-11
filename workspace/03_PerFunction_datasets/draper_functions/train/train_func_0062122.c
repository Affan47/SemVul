bestx(int b, int loops){
	int bestx = 0, bestxt = 0;
	int x, xt, i, j;

	for(x=0; x<256; x++){
		xt = 0;
		for(i=0; i<loops; i++){
			for(j=0; j<16; j++){
				in[j] = xrandom() >> 16;
			}
			in[b] = x;
			xt += aescycles(); xt += aescycles(); xt += aescycles();
			xt += aescycles(); xt += aescycles();
		}
		if(xt>bestxt){
			bestx = x, bestxt = xt;
		}
	}
	return bestx;
}
