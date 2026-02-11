setup_slot_coalesced_allocno_live_ranges (ira_allocno_t allocno)
{
  int i, n;
  ira_allocno_t a;
  live_range_t r;

  n = ALLOCNO_TEMP (allocno);
  for (a = ALLOCNO_NEXT_COALESCED_ALLOCNO (allocno);;
       a = ALLOCNO_NEXT_COALESCED_ALLOCNO (a))
    {
      int nr = ALLOCNO_NUM_OBJECTS (a);
      for (i = 0; i < nr; i++)
	{
	  ira_object_t obj = ALLOCNO_OBJECT (a, i);
	  r = ira_copy_live_range_list (OBJECT_LIVE_RANGES (obj));
	  slot_coalesced_allocnos_live_ranges[n]
	    = ira_merge_live_ranges
	    (slot_coalesced_allocnos_live_ranges[n], r);
	}
      if (a == allocno)
	break;
    }
}
