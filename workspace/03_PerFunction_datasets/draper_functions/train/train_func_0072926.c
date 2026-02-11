propvalue(char *buffer, int size)
{
  char *p = buffer;

  match('[');
  while (lookahead != ']' && lookahead != EOF) {
    if (lookahead == '\\') {
      lookahead = sgf_getch();

      if (lookahead == '\r') {
	lookahead = sgf_getch();
	if (lookahead == '\n')
	  lookahead = sgf_getch();
      }
      else if (lookahead == '\n') {
	lookahead = sgf_getch();
	if (lookahead == '\r')
	  lookahead = sgf_getch();
      }
    }
    if (size > 1) {
      *p++ = lookahead;
      size--;
    }
    lookahead = sgf_getch();
  }
  match(']');


  --p;
  while (p > buffer && isspace((int) (unsigned char) *p))
    --p;
  *++p = '\0';
}
