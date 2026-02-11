direct_declarator (type_p ty, const char **namep, options_p *optsp)
{


  switch (token ())
    {
    case GTY_TOKEN:
      *optsp = gtymarker ();

    case ID:
      *namep = require (ID);
      break;

    case '(':
      advance ();
      ty = inner_declarator (ty, namep, optsp);
      require (')');
      break;

    default:
      parse_error ("expected '(', 'GTY', or an identifier, have %s",
		   print_cur_token ());


      if (token () != '}')
	advance ();
      return 0;
    }
  return array_and_function_declarators_opt (ty);
}
