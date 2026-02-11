parse_c_expression (string)
     char *string;
{
  lexptr = string;


  if (setjmp (parse_return_error))
    return 0;

  if (yyparse () != 0)
    abort ();

  if (*lexptr != '\n')
    error ("Junk after end of expression.");

  return expression_value;
}
