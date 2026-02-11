PS_printM(ParaSparse *M)
{
	int r,n;

	for(r = 0; r < M->size; r++)
	{
		if(r == M->rank)
		{
			printf("Rank %d of %d: na=%d nd=%d\n", M->rank, M->size, M->na, M->nd);
			for(n = 0; n < M->Ne; n++)
				printf("%d %d %lg\n",M->i[n],M->j[n],M->Mij[n]);
		}
		MPI_Barrier(M->comm);
	}

	if(M->rank == 0)
		printf("\n");
}
