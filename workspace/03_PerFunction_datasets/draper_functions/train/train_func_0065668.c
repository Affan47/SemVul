s_set (int equiv)
{
  char *name;


  if ((name = read_symbol_name ()) == NULL)
    return;

  if (*input_line_pointer != ',')
    {
      as_bad (_("expected comma after \"%s\""), name);
      ignore_rest_of_line ();
      free (name);
      return;
    }

  input_line_pointer++;
  assign_symbol (name, equiv);
  demand_empty_rest_of_line ();
  free (name);
}
