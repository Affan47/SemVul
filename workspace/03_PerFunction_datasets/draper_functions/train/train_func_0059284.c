LU_Decompose(const Matrix4x4& M, int *indx)
{
	int  i, imax, j, k;
	double big, dum, sum, temp;
	double vv[4];
	Matrix4x4 LU_M = M;
	int N = 4;

	for(i = 0; i < N; i++){
		big = 0.0;
		for(j = 0; j < N; j++)
			if((temp = fabs(M.row[i][j])) > big)
				big = temp;
		if(big == 0.0)
			cerr << "inverse of singular Matrix4x4" << endl;

		vv[i] = 1.0 / big;
	}

	for(j = 0; j < N; j++){
		for(i = 0; i < j; i++){
			sum = LU_M[i][j];
			for(k = 0; k < i; k++)
				sum -= LU_M[i][k] * LU_M[k][j];
			LU_M[i][j] = sum;
		}
		big = 0.0;
		for(i = j; i < N; i++){
			sum = LU_M[i][j];
			for(k = 0; k < j; k++)
				sum -= LU_M[i][k] * LU_M[k][j];
			LU_M[i][j] = sum;
			if((dum = vv[i]*fabs(sum)) >= big){
				big = dum;
				imax = i;
			}
		}
		if(j != imax){
			for(k = 0; k < N; k++){
				dum = LU_M[imax][k];
				LU_M[imax][k] = LU_M[j][k];
				LU_M[j][k] = dum;
			}
			vv[imax] = vv[j];
		}
		indx[j] = imax;
		if(j < N - 1){
			dum = 1.0 / LU_M[j][j];
			for(i = j + 1; i < N; i++)
				LU_M[i][j] *= dum;
		}
	}

	return LU_M;
}
