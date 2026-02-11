tm_region_init_0 (struct tm_region *outer, basic_block bb, gimple stmt)
{
  struct tm_region *region;

  region = (struct tm_region *)
    obstack_alloc (&tm_obstack.obstack, sizeof (struct tm_region));

  if (outer)
    {
      region->next = outer->inner;
      outer->inner = region;
    }
  else
    {
      region->next = all_tm_regions;
      all_tm_regions = region;
    }
  region->inner = NULL;
  region->outer = outer;

  region->transaction_stmt = stmt;
  region->original_transaction_was_outer = false;
  region->tm_state = NULL;


  region->entry_block = FALLTHRU_EDGE (bb)->dest;

  region->exit_blocks = BITMAP_ALLOC (&tm_obstack);
  region->irr_blocks = BITMAP_ALLOC (&tm_obstack);

  return region;
}
