Problem_6(MATRIX &matrix){
    int N = matrix.size();
    if(N<=1)
	return;
    int numRound = N/2;
    for(int i=0; i<numRound; ++i){

	for(int j=i; j<N-i-1; ++j){
	    int temp = matrix[i][j];
	    matrix[i][j]=matrix[N-1-j][i];
	    matrix[N-1-j][i]=matrix[N-1-i][N-1-j];
	    matrix[N-1-i][N-1-j]=matrix[j][N-1-i];
	    matrix[j][N-1-i]=temp;
	}
    }
}
