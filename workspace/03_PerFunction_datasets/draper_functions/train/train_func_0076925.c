color_allocnos (void)
{
  unsigned int i, n;
  bitmap_iterator bi;
  ira_allocno_t a;

  if (flag_ira_algorithm == IRA_ALGORITHM_PRIORITY)
    {
      n = 0;
      EXECUTE_IF_SET_IN_BITMAP (coloring_allocno_bitmap, 0, i, bi)
	{
	  a = ira_allocnos[i];
	  if (ALLOCNO_COVER_CLASS (a) == NO_REGS)
	    {
	      ALLOCNO_HARD_REGNO (a) = -1;
	      ALLOCNO_ASSIGNED_P (a) = true;
	      ira_assert (ALLOCNO_UPDATED_HARD_REG_COSTS (a) == NULL);
	      ira_assert (ALLOCNO_UPDATED_CONFLICT_HARD_REG_COSTS (a) == NULL);
	      if (internal_flag_ira_verbose > 3 && ira_dump_file != NULL)
		{
		  fprintf (ira_dump_file, "      Spill");
		  ira_print_expanded_allocno (a);
		  fprintf (ira_dump_file, "\n");
		}
	      continue;
	    }
	  sorted_allocnos[n++] = a;
	}
      if (n != 0)
	{
	  setup_allocno_priorities (sorted_allocnos, n);
	  qsort (sorted_allocnos, n, sizeof (ira_allocno_t),
		 allocno_priority_compare_func);
	  for (i = 0; i < n; i++)
	    {
	      a = sorted_allocnos[i];
	      if (internal_flag_ira_verbose > 3 && ira_dump_file != NULL)
		{
		  fprintf (ira_dump_file, "      ");
		  ira_print_expanded_allocno (a);
		  fprintf (ira_dump_file, "  -- ");
		}
	      if (assign_hard_reg (a, false))
		{
		  if (internal_flag_ira_verbose > 3 && ira_dump_file != NULL)
		    fprintf (ira_dump_file, "assign hard reg %d\n",
			     ALLOCNO_HARD_REGNO (a));
		}
	      else
		{
		  if (internal_flag_ira_verbose > 3 && ira_dump_file != NULL)
		    fprintf (ira_dump_file, "assign memory\n");
		}
	    }
	}
    }
  else
    {

      colorable_allocno_bucket = NULL;
      uncolorable_allocno_bucket = NULL;
      EXECUTE_IF_SET_IN_BITMAP (coloring_allocno_bitmap, 0, i, bi)
	{
	  a = ira_allocnos[i];
	  if (ALLOCNO_COVER_CLASS (a) == NO_REGS)
	    {
	      ALLOCNO_HARD_REGNO (a) = -1;
	      ALLOCNO_ASSIGNED_P (a) = true;
	      ira_assert (ALLOCNO_UPDATED_HARD_REG_COSTS (a) == NULL);
	      ira_assert (ALLOCNO_UPDATED_CONFLICT_HARD_REG_COSTS (a) == NULL);
	      if (internal_flag_ira_verbose > 3 && ira_dump_file != NULL)
		{
		  fprintf (ira_dump_file, "      Spill");
		  ira_print_expanded_allocno (a);
		  fprintf (ira_dump_file, "\n");
		}
	      continue;
	    }
	  put_allocno_into_bucket (a);
	}
      push_allocnos_to_stack ();
      pop_allocnos_from_stack ();
    }
}
