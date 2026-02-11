ADIOI_Free_fn(void *ptr, int lineno, char *fname)
{
    if (!ptr) {
	FPRINTF(stderr, "Attempt to free null pointer in file %s, line %d\n", fname, lineno);
	MPI_Abort(MPI_COMM_WORLD, 1);
    }

    free(ptr);
}
