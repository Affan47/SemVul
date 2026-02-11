input_iarray(int nval, int *array)
{
  int i, n;
  int ival = 0;

  for ( i = 0; i < nval; i++ )
    {
      n = scanf("%d", &array[i]);
      if ( n != 1 ) break;

      ival++;
    }

  return (ival);
}
