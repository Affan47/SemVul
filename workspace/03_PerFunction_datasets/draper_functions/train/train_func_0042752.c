builtin_usage ()
{
  if (this_command_name && *this_command_name)
    fprintf (stderr, _("%s: usage: "), this_command_name);
  fprintf (stderr, "%s\n", current_builtin->short_doc);
  fflush (stderr);
}
