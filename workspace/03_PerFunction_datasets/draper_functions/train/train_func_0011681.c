mems_in_disjoint_alias_sets_p (mem1, mem2)
     rtx mem1;
     rtx mem2;
{
#ifdef ENABLE_CHECKING


  if (! flag_strict_aliasing
      && (MEM_ALIAS_SET (mem1) != 0 || MEM_ALIAS_SET (mem2) != 0))
    abort ();
#endif

  return ! alias_sets_conflict_p (MEM_ALIAS_SET (mem1), MEM_ALIAS_SET (mem2));
}
