increment_internal_index (A68_TUPLE * tup, int dim)
{
  BOOL_T carry = A68_TRUE;
  int k;
  for (k = dim - 1; k >= 0 && carry; k--) {
    A68_TUPLE *ref = &tup[k];
    if (K (ref) < UPB (ref)) {
      (K (ref))++;
      carry = A68_FALSE;
    } else {
      K (ref) = LWB (ref);
    }
  }
  return (carry);
}
