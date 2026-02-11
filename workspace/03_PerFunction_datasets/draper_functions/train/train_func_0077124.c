EvalPartition(superblock_t *seg_list, seg_t *part,
    int best_cost)
{
  eval_info_t info;


  info.cost   = 0;
  info.splits = 0;
  info.iffy   = 0;
  info.near_miss  = 0;

  info.real_left  = 0;
  info.real_right = 0;
  info.mini_left  = 0;
  info.mini_right = 0;

  if (EvalPartitionWorker(seg_list, part, best_cost, &info))
    return -1;


  if (info.real_left == 0 || info.real_right == 0)
  {
#   if DEBUG_PICKNODE
    PrintDebug("Eval : No real segs on %s%sside\n",
        info.real_left  ? "" : "left ",
        info.real_right ? "" : "right ");
#   endif

    return -1;
  }


  info.cost += 100 * ABS(info.real_left - info.real_right);


  info.cost += 50 * ABS(info.mini_left - info.mini_right);


  if (part->pdx != 0 && part->pdy != 0)
    info.cost += 25;

# if DEBUG_PICKNODE
  PrintDebug("Eval %p: splits=%d iffy=%d near=%d left=%d+%d right=%d+%d "
      "cost=%d.%02d\n", part, info.splits, info.iffy, info.near_miss,
      info.real_left, info.mini_left, info.real_right, info.mini_right,
      info.cost / 100, info.cost % 100);
# endif

  return info.cost;
}
