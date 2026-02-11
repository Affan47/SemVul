linear_algebra_clear(linalg_t * la_inf, QS_t * qs_inf)
{
   la_col_t * matrix = la_inf->matrix;
   la_col_t * unmerged = la_inf->unmerged;
   mpz_t * Y_arr = la_inf->Y_arr;
   const unsigned long buffer_size = 3*(qs_inf->num_primes + EXTRA_RELS + 100)/2;

   for (unsigned long i = 0; i < buffer_size; i++)
   {
      mpz_clear(Y_arr[i]);
   }

   for (unsigned long i = 0; i < la_inf->columns; i++)
   {
      free_col(matrix + i);
   }

   for (unsigned long i = 0; i < la_inf->num_unmerged; i++)
   {
      free_col(unmerged + i);
   }

   flint_stack_release();
   flint_stack_release();
   flint_stack_release();
   flint_stack_release();
   flint_stack_release();
   flint_stack_release();
}
