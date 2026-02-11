range_cmp_range1(struct range_range_t *range,
		 md_addr_t addr,
		 counter_t icount,
		 counter_t cycle)
{
  if (range->start.ptype != range->end.ptype)
    panic("invalid range");

  switch (range->start.ptype)
    {
    case pt_addr:
      if (addr < (md_addr_t)range->start.pos)
	return -1;
      else if ((md_addr_t)range->start.pos <= addr && addr <= (md_addr_t)range->end.pos)
	return 0;
      else
	return 1;
      break;
    case pt_inst:
      if (icount < range->start.pos)
	return -1;
      else if (range->start.pos <= icount && icount <= range->end.pos)
	return 0;
      else
	return 1;
      break;
    case pt_cycle:
      if (cycle < range->start.pos)
	return -1;
      else if (range->start.pos <= cycle && cycle <= range->end.pos)
	return 0;
      else
	return 1;
      break;
    default:
      panic("bogus range type");
    }
}
