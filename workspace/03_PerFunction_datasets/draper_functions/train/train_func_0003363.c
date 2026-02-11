ergo_csr_find_index_inline(const csr_matrix_struct* csr, int row, int col)
{
  int n = csr->rowList[row].noOfElementsInRow;
  int baseIndex = csr->rowList[row].firstElementIndex;
  int* colList = &csr->columnIndexList[baseIndex];
  int lo = 0;
  int hi = n-1;
  while(lo < hi - 1)
    {
      int mid = (lo + hi) / 2;
      if(colList[mid] < col)
	lo = mid;
      else
	hi = mid;
    }
  if(colList[lo] == col)
    return baseIndex + lo;
  if(colList[hi] == col)
    return baseIndex + hi;

  return -1;
}
