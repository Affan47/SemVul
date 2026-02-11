scm_c_make_bitvector (size_t len, SCM fill)
{
  size_t word_len = (len + 31) / 32;
  scm_t_uint32 *bits;
  SCM res;

  bits = scm_gc_malloc (sizeof (scm_t_uint32) * word_len,
			"bitvector");
  SCM_NEWSMOB2 (res, scm_tc16_bitvector, bits, len);

  if (!SCM_UNBNDP (fill))
    scm_bitvector_fill_x (res, fill);

  return res;
}
