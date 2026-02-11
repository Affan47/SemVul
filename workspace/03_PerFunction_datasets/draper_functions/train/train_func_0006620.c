ssa_conflicts_merge (ssa_conflicts_p ptr, unsigned x, unsigned y)
{
  unsigned z;
  bitmap_iterator bi;
  bitmap bx = ptr->conflicts[x];
  bitmap by = ptr->conflicts[y];

  gcc_checking_assert (x != y);
  if (! by)
    return;


  EXECUTE_IF_SET_IN_BITMAP (by, 0, z, bi)
    {
      bitmap bz = ptr->conflicts[z];
      if (bz)
	bitmap_set_bit (bz, x);
    }

  if (bx)
    {

      bitmap_ior_into (bx, by);
      BITMAP_FREE (by);
      ptr->conflicts[y] = NULL;
    }
  else
    {

      ptr->conflicts[x] = by;
      ptr->conflicts[y] = NULL;
    }
}
