consume_balanced (int opener, int closer)
{
  require (opener);
  for (;;)
    switch (token ())
      {
      default:
	advance ();
	break;
      case '(':
	consume_balanced ('(', ')');
	break;
      case '[':
	consume_balanced ('[', ']');
	break;
      case '{':
	consume_balanced ('{', '}');
	break;

      case '}':
      case ']':
      case ')':
	if (token () != closer)
	  parse_error ("unbalanced delimiters - expected '%c', have '%c'",
		       closer, token ());
      advance ();
      return;

      case EOF_TOKEN:
	parse_error ("unexpected end of file within %c%c-delimited construct",
		     opener, closer);
	return;
      }
}
