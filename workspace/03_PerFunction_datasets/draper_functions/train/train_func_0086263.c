gsl_combination_init_first (gsl_combination * c)
{
  const size_t k = c->k ;
  size_t i;


  for (i = 0; i < k; i++)
    {
      c->data[i] = i;
    }
}
