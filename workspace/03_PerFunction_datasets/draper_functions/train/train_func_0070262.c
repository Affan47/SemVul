free_loop_data (struct loop *loop)
{
  struct loop_data *data = LOOP_DATA (loop);
  if (!data)
    return;

  bitmap_clear (&LOOP_DATA (loop)->regs_ref);
  bitmap_clear (&LOOP_DATA (loop)->regs_live);
  free (data);
  loop->aux = NULL;
}
