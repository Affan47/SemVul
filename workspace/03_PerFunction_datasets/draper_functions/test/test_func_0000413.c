Print(int Size, int *b)
{
  int a, i, j, k, l;
  mexPrintf("   ");
  for (k = 0; k < Size*periods; k++)
    mexPrintf("%-2d ", k);
  mexPrintf("    |    ");
  for (k = 0; k < Size*periods; k++)
    mexPrintf("%8d", k);
  mexPrintf("\n");
  for (i = 0; i < Size*periods; i++)
    {
      NonZeroElem *first = FNZE_R[i];
      j = NbNZRow[i];
      mexPrintf("%-2d ", i);
      a = 0;
      for (k = 0; k < j; k++)
        {
          for (l = 0; l < (first->c_index-a); l++)
            mexPrintf("   ");
          mexPrintf("%-2d ", first->u_index);
          a = first->c_index+1;
          first = first->NZE_R_N;
        }
      for (k = a; k < Size*periods; k++)
        mexPrintf("   ");
      mexPrintf("%-2d ", b[i]);

      first = FNZE_R[i];
      j = NbNZRow[i];
      mexPrintf(" | %-2d ", i);
      a = 0;
      for (k = 0; k < j; k++)
        {
          for (l = 0; l < (first->c_index-a); l++)
            mexPrintf("        ");
          mexPrintf("%8.4f", double (u[first->u_index]));
          a = first->c_index+1;
          first = first->NZE_R_N;
        }
      for (k = a; k < Size*periods; k++)
        mexPrintf("        ");
      mexPrintf("%8.4f", double (u[b[i]]));
      mexPrintf("\n");
    }
}
