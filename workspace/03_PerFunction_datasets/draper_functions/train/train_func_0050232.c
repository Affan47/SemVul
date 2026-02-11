matrix_test_chol_Nx6x6_sparse(int DIM, int a2)
{
	CMatrixDouble  C(DIM*6,DIM*6);
	for (int i=0;i<DIM;i++)
	{
		CMatrixDouble subCov = randomGenerator.drawDefinitePositiveMatrix(6, 0.2);
		C.insertMatrix(i*6,i*6,subCov);
	}

	const CSparseMatrix  SM(C);

	const long N = 100;
	CTicTac	 tictac;
	for (long i=0;i<N;i++)
	{
		CSparseMatrix::CholeskyDecomp  CHOL(SM);
	}
	return tictac.Tac()/N;
}
