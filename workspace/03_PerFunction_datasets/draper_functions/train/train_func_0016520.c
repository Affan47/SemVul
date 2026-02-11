scm_malloc_obj (size_t n)
{
  scm_t_bits mem = n ? (scm_t_bits) scm_gc_malloc (n, "malloc smob") : 0;
  if (n && !mem)
    return SCM_BOOL_F;
  SCM_RETURN_NEWSMOB (scm_tc16_malloc, mem);
}
