translate_quadstrip_uint2uint_first2first(
    const void * _in,
    unsigned start,
    unsigned nr,
    void *_out )
{
  const uint*in = (const uint*)_in;
  uint *out = (uint*)_out;
  unsigned i, j;
  (void)j;
  for (i = start, j = 0; j < nr; j+=6, i+=2) {
      (out+j+0)[0] = (uint)in[i+2];
      (out+j+0)[1] = (uint)in[i+0];
      (out+j+0)[2] = (uint)in[i+3];
      (out+j+3)[0] = (uint)in[i+0];
      (out+j+3)[1] = (uint)in[i+1];
      (out+j+3)[2] = (uint)in[i+3];
   }
}
