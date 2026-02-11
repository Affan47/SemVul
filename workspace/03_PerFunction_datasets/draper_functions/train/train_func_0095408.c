get_def_blocks_for (common_info_p info)
{
  struct def_blocks_d *db_p = &info->def_blocks;
  if (!db_p->def_blocks)
    {
      db_p->def_blocks = BITMAP_ALLOC (&update_ssa_obstack);
      db_p->phi_blocks = BITMAP_ALLOC (&update_ssa_obstack);
      db_p->livein_blocks = BITMAP_ALLOC (&update_ssa_obstack);
    }

  return db_p;
}
