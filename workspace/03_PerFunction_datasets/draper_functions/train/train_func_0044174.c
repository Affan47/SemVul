read_name(istream& in, char* buf, int bufsiz) {
  char close_paren = ')';
  char key = ':';
  char lookahead;
  ParamList::skip_space(in);
  in.get(lookahead);


  if (lookahead == ':' || lookahead == ')') {
    in.putback(lookahead);
    return -1;
  }
  if (lookahead != ',')
    in.putback(lookahead);
  else
    ParamList::skip_space(in);

  ParamList::parse_token(in, buf, bufsiz);
  return 0;
}
