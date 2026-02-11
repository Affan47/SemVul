rffts1(float *ioptr, long M, long Rows, float *Utbl, short *BRLow){


float	scale;
long 	StageCnt;
long 	NDiffU;

M=M-1;
switch (M){
case -1:
	break;
case 0:
	for (;Rows>0;Rows--){
		rfft1pt(ioptr);
		ioptr += 2*POW2(M);
	}
case 1:
	for (;Rows>0;Rows--){
		rfft2pt(ioptr);
		ioptr += 2*POW2(M);
	}
	break;
case 2:
	for (;Rows>0;Rows--){
		rfft4pt(ioptr);
		ioptr += 2*POW2(M);
	}
	break;
case 3:
	for (;Rows>0;Rows--){
		rfft8pt(ioptr);
		ioptr += 2*POW2(M);
	}
	break;
default:
	scale = 0.5;
	for (;Rows>0;Rows--){

		scbitrevR2(ioptr, M, BRLow, scale);

		StageCnt = (M-1) / 3;
		NDiffU = 2;

		if ( (M-1-(StageCnt * 3)) == 1 ){
			bfR2(ioptr, M, NDiffU);
			NDiffU *= 2;
		}

		if ( (M-1-(StageCnt * 3)) == 2 ){
			bfR4(ioptr, M, NDiffU);
			NDiffU *= 4;
		}

		if (M <= MCACHE){
			bfstages(ioptr, M, Utbl, 2, NDiffU, StageCnt);
			frstage(ioptr, M+1, Utbl);
		}

		else{
			fftrecurs(ioptr, M, Utbl, 2, NDiffU, StageCnt);
			frstage(ioptr, M+1, Utbl);
		}

		ioptr += 2*POW2(M);
	}
}
}
