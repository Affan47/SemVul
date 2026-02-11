generate_tristrip_ushort_last2first(
    unsigned start,
    unsigned nr,
    void *_out )
{
  ushort *out = (ushort*)_out;
  unsigned i, j;
  (void)j;
  for (i = start, j = 0; j < nr; j+=3, i++) {
      (out+j)[0] = (ushort)(i+2);
      (out+j)[1] = (ushort)(i+(i&1));
      (out+j)[2] = (ushort)(i+1-(i&1));
   }
}
