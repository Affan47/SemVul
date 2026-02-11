check_one (const char *name, int i,
           mp_srcptr src, mp_limb_t n,
           mp_srcptr got, mp_srcptr want, mp_size_t size)
{
  if (! refmpn_equal_anynail (got, want, size))
    {
      printf ("Wrong at %s i=%d\n", name, i);
      mpn_trace ("  src", src,  size);
      mpn_trace ("    n", &n,   (mp_size_t) 1);
      mpn_trace ("  got", got,  size);
      mpn_trace (" want", want, size);
      abort ();
    }
}
