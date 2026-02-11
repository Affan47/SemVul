property(SGFNode *n, SGFProperty *last)
{
  char name[3];
  char buffer[4000];

  propident(name, sizeof(name));
  do {
    propvalue(buffer, sizeof(buffer));
    last = sgfMkProperty(name, buffer, n, last);
  } while (lookahead == '[');
  return last;
}
