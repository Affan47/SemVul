opustex_print_note (FILE * f, char pitch)
{
  if (is_even (otexclef))
    {
      if (pitch - otexclef < 104)
	{
	  fprintf (f, "%c", pitch - otexclef - 25);
	}
      else
	{
	  fprintf (f, "%c", pitch - otexclef - 7);
	}
    }
  else
    {
      if (pitch - otexclef < 97)
	{
	  fprintf (f, "%c", pitch - otexclef - 18);
	}
      else
	{
	  fprintf (f, "%c", pitch - otexclef);
	}
    }
}
