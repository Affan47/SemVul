consume_until_eos (void)
{
  for (;;)
    switch (token ())
      {
      case ';':
	advance ();
	return;

      case '{':
	consume_balanced ('{', '}');
	return;

      case '(':
	consume_balanced ('(', ')');
	break;

      case '[':
	consume_balanced ('[', ']');
	break;

      case '}':
      case ']':
      case ')':
	parse_error ("unmatched '%c' while scanning for ';'", token ());
	return;

      case EOF_TOKEN:
	parse_error ("unexpected end of file while scanning for ';'");
	return;

      default:
	advance ();
	break;
      }
}
