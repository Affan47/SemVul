history_total_bytes ()
{
  register int i, result;

  for (i = result = 0; the_history && the_history[i]; i++)
    result += HISTENT_BYTES (the_history[i]);

  return (result);
}
