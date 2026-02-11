exp5 ()
{
  register intmax_t val1, val2;

  val1 = exp4 ();

  while ((curtok == EQEQ) || (curtok == NEQ))
    {
      int op = curtok;

      readtok ();
      val2 = exp4 ();
      if (op == EQEQ)
	val1 = (val1 == val2);
      else if (op == NEQ)
	val1 = (val1 != val2);
    }
  return (val1);
}
