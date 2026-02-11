btr_def_live_range (btr_def def, HARD_REG_SET *btrs_live_in_range)
{
  if (!def->live_range)
    {
      btr_user user;

      def->live_range = BITMAP_XMALLOC ();

      bitmap_set_bit (def->live_range, def->bb->index);
      COPY_HARD_REG_SET (*btrs_live_in_range, btrs_live[def->bb->index]);

      for (user = def->uses; user != NULL; user = user->next)
	augment_live_range (def->live_range, btrs_live_in_range,
			    def->bb, user->bb);
    }
  else
    {


      int bb;

      CLEAR_HARD_REG_SET (*btrs_live_in_range);
      EXECUTE_IF_SET_IN_BITMAP
	(def->live_range, 0, bb,
	 {
	   IOR_HARD_REG_SET (*btrs_live_in_range,
	     btrs_live[bb]);
	 });
    }
  if (!def->other_btr_uses_before_def &&
      !def->other_btr_uses_after_use)
    CLEAR_HARD_REG_BIT (*btrs_live_in_range, def->btr);
}
