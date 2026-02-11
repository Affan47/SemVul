sets_sort (sets_long_t *sets)
{
  unsigned long i, nr_unsorted, highest_swap;
  set_long_t *set;


  nr_unsorted = sets->nr;
  while (nr_unsorted > 1UL)
    {
      outputf (OUTPUT_TRACE, "nr_unsorted = %lu. ", nr_unsorted);
      sets_print (OUTPUT_TRACE, sets);
      set = sets->sets;
      highest_swap = 1UL;
      for (i = 1UL; i < nr_unsorted; i++)
	{
	  if (set->card > sets_nextset(set)->card)
	    {
	      outputf (OUTPUT_TRACE, "sets_sort: swapping %lu and %lu\n",
                       i - 1, i);
	      set_swap (set);
	      highest_swap = i;
	    }
          set = sets_nextset (set);
	}
      nr_unsorted = highest_swap;
    }

#ifdef WANT_ASSERT
  set = sets->sets;
  for (i = 0UL; i + 1UL < sets->nr; i++)
    {
      ASSERT(set->card <= sets_nextset (set)->card);
      set = sets_nextset (set);
    }
#endif
}
