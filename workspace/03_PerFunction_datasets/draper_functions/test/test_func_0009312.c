get_stuff_in_command ()
{
  tos++;
  check_range ();
  init_string (tos);

  while (at (ptr, idx))
    {
      if (iscommand (ptr, idx))
	break;
      idx = copy_past_newline (ptr, idx, tos);
    }
  pc++;
}
