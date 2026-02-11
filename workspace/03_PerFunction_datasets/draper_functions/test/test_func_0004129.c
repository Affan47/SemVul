write_state_nested_option (options_p current)
{
  fprintf (state_file, "nested ");
  write_state_type (current->info.nested->type);
  if (current->info.nested->convert_from != NULL)
    write_state_a_string (current->info.nested->convert_from);
  else
    fprintf (state_file, " nil ");

  if (current->info.nested->convert_to != NULL)
    write_state_a_string (current->info.nested->convert_to);
  else
    fprintf (state_file, " nil ");
}
