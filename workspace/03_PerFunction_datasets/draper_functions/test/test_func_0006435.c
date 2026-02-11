deregister_tm_clones (void)
{
  void (*fn) (void *);

#ifdef HAVE_GAS_HIDDEN
  if (__TMC_END__ - __TMC_LIST__ == 0)
    return;
#else
  if (__TMC_LIST__[0] == NULL)
    return;
#endif

  fn = _ITM_deregisterTMCloneTable;
  __asm ("" : "+r" (fn));
  if (fn)
    fn (__TMC_LIST__);
}
