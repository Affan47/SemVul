read(FILE *input)
{
  constants.clear();
  int size = Compression::multibyte_read(input);
  for(int i = 0; i != size; i++)
  {
    wstring mystr = Compression::wstring_read(input);
    constants[mystr] = Compression::multibyte_read(input);
  }
}
