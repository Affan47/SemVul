translate_tris_uint2uint_last2first(
    const void * _in,
    unsigned start,
    unsigned nr,
    void *_out )
{
  const uint*in = (const uint*)_in;
  uint *out = (uint*)_out;
  unsigned i, j;
  (void)j;
  for (i = start; i < (nr+start); i+=3) {
      (out+i)[0] = (uint)in[i+2];
      (out+i)[1] = (uint)in[i];
      (out+i)[2] = (uint)in[i+1];
   }
}
