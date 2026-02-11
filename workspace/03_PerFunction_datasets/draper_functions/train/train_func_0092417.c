addString(const char * string)
{
  int position = string_.hash(string);
  if (position<0) {
    position = string_.numberItems();
    string_.addHash(position,string);
  }
  return position;
}
