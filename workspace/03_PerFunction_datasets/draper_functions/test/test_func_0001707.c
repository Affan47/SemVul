insert_loop_mem (rtx *mem, void *data ATTRIBUTE_UNUSED)
{
  struct loop_info *loop_info = data;
  int i;
  rtx m = *mem;

  if (m == NULL_RTX)
    return 0;

  switch (GET_CODE (m))
    {
    case MEM:
      break;

    case CLOBBER:

      return -1;

    case CONST_DOUBLE:


      return -1;

    case EXPR_LIST:

      return -1;

    default:

      return 0;
    }


  for (i = 0; i < loop_info->mems_idx; ++i)
    if (rtx_equal_p (m, loop_info->mems[i].mem))
      {
	if (MEM_VOLATILE_P (m) && !MEM_VOLATILE_P (loop_info->mems[i].mem))
	  loop_info->mems[i].mem = m;
	if (GET_MODE (m) != GET_MODE (loop_info->mems[i].mem))


	  loop_info->mems[i].optimize = 0;

	return 0;
      }


  if (loop_info->mems_idx == loop_info->mems_allocated)
    {
      if (loop_info->mems_allocated != 0)
	loop_info->mems_allocated *= 2;
      else
	loop_info->mems_allocated = 32;

      loop_info->mems = xrealloc (loop_info->mems,
				  loop_info->mems_allocated * sizeof (loop_mem_info));
    }


  loop_info->mems[loop_info->mems_idx].mem = m;


  loop_info->mems[loop_info->mems_idx].optimize = (GET_MODE (m) != BLKmode);
  loop_info->mems[loop_info->mems_idx].reg = NULL_RTX;
  ++loop_info->mems_idx;

  return 0;
}
