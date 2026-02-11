iffts1(float *ioptr, long M, long Rows, float *Utbl, short *BRLow){


long 	StageCnt;
long 	NDiffU;
const float scale = 1.0/POW2(M);

switch (M){
case 0:
	break;
case 1:
	for (;Rows>0;Rows--){
		ifft2pt(ioptr, scale);
		ioptr += 2*POW2(M);
	}
	break;
case 2:
	for (;Rows>0;Rows--){
		ifft4pt(ioptr, scale);
		ioptr += 2*POW2(M);
	}
	break;
case 3:
	for (;Rows>0;Rows--){
		ifft8pt(ioptr, scale);
		ioptr += 2*POW2(M);
	}
	break;
default:
	for (;Rows>0;Rows--){

		scbitrevR2(ioptr, M, BRLow, scale);

		StageCnt = (M-1) / 3;
		NDiffU = 2;

		if ( (M-1-(StageCnt * 3)) == 1 ){
			ibfR2(ioptr, M, NDiffU);
			NDiffU *= 2;
		}

		if ( (M-1-(StageCnt * 3)) == 2 ){
			ibfR4(ioptr, M, NDiffU);
			NDiffU *= 4;
		}

		if (M <= MCACHE)
			ibfstages(ioptr, M, Utbl, 1, NDiffU, StageCnt);

		else{
			ifftrecurs(ioptr, M, Utbl, 1, NDiffU, StageCnt);
		}

		ioptr += 2*POW2(M);
	}
}
}
