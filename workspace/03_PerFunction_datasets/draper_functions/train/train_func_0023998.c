set_loop_copy (struct loop *loop, struct loop *copy)
{
  if (!copy)
    copy_original_table_clear (loop_copy, loop->num);
  else
    copy_original_table_set (loop_copy, loop->num, copy->num);
}
