dump_recorded_exits (FILE *file)
{
  if (!current_loops->exits)
    return;
  htab_traverse (current_loops->exits, dump_recorded_exit, file);
}
