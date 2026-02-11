ddf_get_matrix_from_vector_storage_sparse(const char* p, size_t sizeInBytes, int n, int* rowind2, int* colind2, ergo_real* values2)
{
  int nBytesPerElement = sizeof(ergo_real)+2*sizeof(int);
  if(sizeInBytes % nBytesPerElement != 0)
    return -1;
  long nvalues = sizeInBytes / nBytesPerElement;
  int* rowind = (int*)p;
  int* colind = &rowind[nvalues];
  ergo_real* values = (ergo_real*)(&rowind[2*nvalues]);
  for(long i = 0; i < nvalues; i++)
    {
      rowind2[i] = rowind[i];
      colind2[i] = colind[i];
      values2[i] = values[i];
    }
  return 0;
}
