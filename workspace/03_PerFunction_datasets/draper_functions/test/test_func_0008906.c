check_jmp_inner_loop(Block *bpt)
{
  if (is_do_loop(bpt))
    if (!block_has_outer_jump(bpt))
      return (FALSE);

  if(bpt->inner != NULL)
    if (check_jmp_inner_loop(bpt->inner) == FALSE)
      return (FALSE);
  if(bpt->next  != NULL)
    if (check_jmp_inner_loop(bpt->next) == FALSE)
      return (FALSE);

  return (TRUE);
}
