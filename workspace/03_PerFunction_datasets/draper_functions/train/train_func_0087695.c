rs_deallocmatINT(int ***v, int m)
{
  for (int i = 0; i < m; ++i) {
    free(reinterpret_cast<void *> ((*v)[i]));
  }
  free(reinterpret_cast<void *> (*v));
}
