__check_break(md_addr_t next_PC,
	      int access,
	      md_addr_t addr,
	      counter_t icount,
	      counter_t cycle)
{
  struct dlite_break_t *bp;

  if (dlite_active)
    {

      break_access = 0;
      return TRUE;
    }


  for (bp=dlite_bps; bp != NULL; bp=bp->next)
    {
      switch (bp->range.start.ptype)
	{
	case pt_addr:
	  if ((bp->class & ACCESS_EXEC)
	      && !range_cmp_range(&bp->range, next_PC))
	    {

	      myfprintf(stdout,
			"Stopping at code breakpoint #%d @ 0x%08p...\n",
			bp->id, next_PC);
	      break_access = ACCESS_EXEC;
	      return TRUE;
	    }
	  if ((bp->class & ACCESS_READ)
	      && ((access & ACCESS_READ)
		  && !range_cmp_range(&bp->range, addr)))
	    {

	      myfprintf(stdout,
			"Stopping at read breakpoint #%d @ 0x%08p...\n",
			bp->id, addr);
	      break_access = ACCESS_READ;
	      return TRUE;
	    }
	  if ((bp->class & ACCESS_WRITE)
	      && ((access & ACCESS_WRITE)
		  && !range_cmp_range(&bp->range, addr)))
	    {

	      myfprintf(stdout,
			"Stopping at write breakpoint #%d @ 0x%08p...\n",
			bp->id, addr);
	      break_access = ACCESS_WRITE;
	      return TRUE;
	    }
	  break;

	case pt_inst:
	  if (!range_cmp_range(&bp->range, icount))
	    {

	      fprintf(stdout,
		      "Stopping at inst count breakpoint #%d @ %.0f...\n",
		      bp->id, (double)icount);
	      break_access = ACCESS_EXEC;
	      return TRUE;
	    }
	  break;

	case pt_cycle:
	  if (!range_cmp_range(&bp->range, cycle))
	    {

	      fprintf(stdout,
		      "Stopping at cycle count breakpoint #%d @ %.0f...\n",
		      bp->id, (double)cycle);
	      break_access = ACCESS_EXEC;
	      return TRUE;
	    }
	  break;

	default:
	  panic("bogus range type");
	}


    }


  break_access = 0;
  return FALSE;
}
