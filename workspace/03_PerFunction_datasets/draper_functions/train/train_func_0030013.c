scm_makcclo (SCM proc, size_t len)
{
  scm_t_bits *base = scm_gc_malloc (len * sizeof (scm_t_bits),
				    "compiled closure");
  unsigned long i;
  SCM s;

  for (i = 0; i < len; ++i)
    base [i] = SCM_UNPACK (SCM_UNSPECIFIED);

  s = scm_cell (SCM_MAKE_CCLO_TAG (len), (scm_t_bits) base);
  SCM_SET_CCLO_SUBR (s, proc);
  return s;
}
