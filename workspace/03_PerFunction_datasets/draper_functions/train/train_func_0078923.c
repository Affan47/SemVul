reachable_handlers (rtx insn)
{
  struct reachable_info info;
  struct eh_region *region;
  tree type_thrown;
  int region_number;

  if (GET_CODE (insn) == JUMP_INSN
      && GET_CODE (PATTERN (insn)) == RESX)
    region_number = XINT (PATTERN (insn), 0);
  else
    {
      rtx note = find_reg_note (insn, REG_EH_REGION, NULL_RTX);
      if (!note || INTVAL (XEXP (note, 0)) <= 0)
	return NULL;
      region_number = INTVAL (XEXP (note, 0));
    }

  memset (&info, 0, sizeof (info));

  region = cfun->eh->region_array[region_number];

  type_thrown = NULL_TREE;
  if (GET_CODE (insn) == JUMP_INSN
      && GET_CODE (PATTERN (insn)) == RESX)
    {


      if (region == NULL)
	return NULL;
      region = region->outer;
    }
  else if (region->type == ERT_THROW)
    {
      type_thrown = region->u.throw.type;
      region = region->outer;
    }

  while (region)
    {
      if (reachable_next_level (region, type_thrown, &info) >= RNL_CAUGHT)
	break;


      if (region->type == ERT_CLEANUP)
	region = region->u.cleanup.prev_try;
      else
	region = region->outer;
    }

  return info.handlers;
}
