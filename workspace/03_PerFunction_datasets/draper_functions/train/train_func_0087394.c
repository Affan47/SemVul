two_arguments ()
{
  if (argv[pos][0] == '!' && argv[pos][1] == '\0')
    return (argv[pos + 1][0] == '\0');
  else if (argv[pos][0] == '-' && argv[pos][2] == '\0')
    {
      if (test_unop (argv[pos]))
	return (unary_operator ());
      else
	test_syntax_error (_("%s: unary operator expected"), argv[pos]);
    }
  else
    test_syntax_error (_("%s: unary operator expected"), argv[pos]);

  return (0);
}
