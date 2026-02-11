collect_spilled_coalesced_allocnos (int *pseudo_regnos, int n,
				    ira_allocno_t *spilled_coalesced_allocnos)
{
  int i, num, regno;
  ira_allocno_t allocno;

  for (num = i = 0; i < n; i++)
    {
      regno = pseudo_regnos[i];
      allocno = ira_regno_allocno_map[regno];
      if (allocno == NULL || ALLOCNO_HARD_REGNO (allocno) >= 0
	  || ALLOCNO_FIRST_COALESCED_ALLOCNO (allocno) != allocno)
	continue;
      spilled_coalesced_allocnos[num++] = allocno;
    }
  return num;
}
