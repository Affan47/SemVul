write_state_pair (pair_p current)
{
  if (current == NULL)
    {
      write_any_indent (0);
      fprintf (state_file, "nil)");
      return;
    }

  begin_s_expr ("pair");

  if (current->name != NULL)
    write_state_a_string (current->name);
  else
    write_state_a_string ("nil");

  write_state_type (current->type);
  write_state_fileloc (&(current->line));
  write_state_options (current->opt);


  end_s_expr ();
}
