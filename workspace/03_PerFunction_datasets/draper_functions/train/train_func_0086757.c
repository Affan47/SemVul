sanitizedName(GBool psmode)
{
  GooString *name;
  char buf[8];
  int i;
  char c;

  name = new GooString();

  if (psmode)
  {


    c = getChar(0);
    if (c >= '0' && c <= '9') {
      name->append('f');
    }
  }

  for (i = 0; i < getLength(); ++i) {
    c = getChar(i);
    if (c <= (char)0x20 || c >= (char)0x7f ||
	c == ' ' ||
	c == '(' || c == ')' || c == '<' || c == '>' ||
	c == '[' || c == ']' || c == '{' || c == '}' ||
	c == '/' || c == '%' || c == '#') {
      sprintf(buf, "#%02x", c & 0xff);
      name->append(buf);
    } else {
      name->append(c);
    }
  }
  return name;
}
