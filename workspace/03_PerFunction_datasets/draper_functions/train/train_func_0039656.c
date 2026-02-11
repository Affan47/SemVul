expshift ()
{
  register intmax_t val1, val2;

  val1 = exp3 ();

  while ((curtok == LSH) || (curtok == RSH))
    {
      int op = curtok;

      readtok ();
      val2 = exp3 ();

      if (op == LSH)
	val1 = val1 << val2;
      else
	val1 = val1 >> val2;
    }

  return (val1);
}
