limit_min_diagonal_values( fptr *m, float *mins_vec, int num)
{
   int i;

   for (i=0; i<num; i++)
      m[i][i] = max(mins_vec[i], m[i][i]);
   return(m);
}
