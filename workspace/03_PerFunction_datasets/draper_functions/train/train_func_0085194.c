df_exit_block_bitmap_verify (bool abort_if_fail)
{
  bitmap_head exit_block_uses;
  bool is_eq;

  bitmap_initialize (&exit_block_uses, &df_bitmap_obstack);
  df_get_exit_block_use_set (&exit_block_uses);

  is_eq = bitmap_equal_p (&exit_block_uses, df->exit_block_uses);

  if (!is_eq && abort_if_fail)
    {
      print_current_pass (stderr);
      fprintf (stderr, "exit_block_uses = ");
      df_print_regset (stderr, &exit_block_uses);
      fprintf (stderr, "df->exit_block_uses = ");
      df_print_regset (stderr, df->exit_block_uses);
      gcc_assert (0);
    }

  bitmap_clear (&exit_block_uses);

  return is_eq;
}
