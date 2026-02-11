visit_count_children(const FMindex *index,
                           Nodecount *parent,
                           GtStackNodecount *stack,
                           Mbtab *tmpmbtab,
                           unsigned long *rangeOccs,
                           GT_UNUSED unsigned int numofchars)
{
  unsigned long rangesize, idx, num_special;
  unsigned int offset;
  Nodecount child;

  gt_assert(parent->lower < parent->upper);
  rangesize = gt_bwtrangesplitallwithoutspecial(tmpmbtab,
                                             rangeOccs,
                                             index,
                                             parent->lower,
                                             parent->upper);
  gt_assert(rangesize <= (unsigned long) numofchars);

  offset = 0U;
  num_special = parent->upper - parent->lower;
  for (idx = 0; idx < rangesize; idx++)
  {
    child.lower = tmpmbtab[idx].lowerbound;
    child.upper = tmpmbtab[idx].upperbound;
    child.leaves = 0UL;
    child.branching = 1UL;
    child.parentOffset = offset + 1U;
    child.visited = false;
    child.on_branch = false;


    if (child.upper - child.lower == parent->upper - parent->lower)
    {

      child.on_branch = true;
      parent->branching--;
      GT_STACK_PUSH(stack, child);
      num_special = 0UL;
      offset++;
    }
    else
    {

      if (child.lower + 1 == child.upper)
      {
        parent->leaves++;
        num_special--;
      }
      else

      {
        if (child.lower == child.upper)
        {

        }
        else
        {
          GT_STACK_PUSH(stack, child);
          offset++;
          num_special -= (child.upper - child.lower);
        }
      }
    }
  }
  parent->leaves += num_special;
}
