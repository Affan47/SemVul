eat_white(istream& strm)
{
  char c = strm.get();

  while ( c == ' ' ||  c == '\t'  ||  c == '\r' || c == '\n' ){
    c = strm.get();
  }

  strm.putback(c);
}
