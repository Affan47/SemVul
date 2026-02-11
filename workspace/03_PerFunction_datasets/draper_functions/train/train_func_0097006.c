fftInit(long M){


int theError = 1;

if ((M >= 0) && (M < 8*sizeof(long))){
	theError = 0;
	if (UtblArray[M] == 0){

		UtblArray[M] = (float *) malloc( (POW2(M)/4+1)*sizeof(float) );
		if (UtblArray[M] == 0)
			theError = 2;
		else{
			fftCosInit(M, UtblArray[M]);
		}
		if (M > 1){
			if (BRLowArray[M/2] == 0){
				BRLowArray[M/2] = (short *) malloc( POW2(M/2-1)*sizeof(short) );
				if (BRLowArray[M/2] == 0)
					theError = 2;
				else{
					fftBRInit(M, BRLowArray[M/2]);
				}
			}
		}
		if (M > 2){
			if (BRLowArray[(M-1)/2] == 0){
				BRLowArray[(M-1)/2] = (short *) malloc( POW2((M-1)/2-1)*sizeof(short) );
				if (BRLowArray[(M-1)/2] == 0)
					theError = 2;
				else{
					fftBRInit(M-1, BRLowArray[(M-1)/2]);
				}
			}
		}
	}
};
return theError;
}
