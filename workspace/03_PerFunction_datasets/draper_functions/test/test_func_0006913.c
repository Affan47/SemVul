close(void)
{
  return internal_table ? hp_close(file) : heap_close(file);
}
