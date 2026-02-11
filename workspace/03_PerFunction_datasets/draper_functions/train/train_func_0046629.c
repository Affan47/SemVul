mpz_mat_clear(mpz_mat_t mat)
{
   for (long i = 0; i < mat->r*mat->c; i++)
      mpz_clear(mat->entries[i]);

   if (mat->entries) flint_heap_free(mat->entries);
	mat->entries = NULL;
	mat->r = 0;
	mat->c = 0;
}
