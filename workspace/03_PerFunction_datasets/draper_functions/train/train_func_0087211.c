translate_tristrip_uint2ushort_first2last(
    const void * _in,
    unsigned start,
    unsigned nr,
    void *_out )
{
  const uint*in = (const uint*)_in;
  ushort *out = (ushort*)_out;
  unsigned i, j;
  (void)j;
  for (i = start, j = 0; j < nr; j+=3, i++) {
      (out+j)[0] = (ushort)in[i+1+(i&1)];
      (out+j)[1] = (ushort)in[i+2-(i&1)];
      (out+j)[2] = (ushort)in[i];
   }
}
