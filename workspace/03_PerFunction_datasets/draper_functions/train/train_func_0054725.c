find_replaceable_exprs (var_map map)
{
  basic_block bb;
  temp_expr_table_p table;
  bitmap ret;

  bitmap_obstack_initialize (&ter_bitmap_obstack);
  table = new_temp_expr_table (map);
  FOR_EACH_BB (bb)
    {
      find_replaceable_in_bb (table, bb);
      gcc_checking_assert (bitmap_empty_p (table->partition_in_use));
    }
  ret = free_temp_expr_table (table);
  bitmap_obstack_release (&ter_bitmap_obstack);
  return ret;
}
