store(String<char> &str)
{
  str += '\0';
  const String<char> *p = table_.lookup(str);
  if (!p) {
    String<char> *tem = new String<char>;
    str.swap(*tem);
    table_.insert(tem);
    p = tem;
  }
  return p->data();
}
