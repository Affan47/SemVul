grow_arrays(int nmax)
{
  for (int m = 0; m < nvector; m++)
    memory->grow(vectors[m],peratom[m]*nmax,"minimize:vector");
}
