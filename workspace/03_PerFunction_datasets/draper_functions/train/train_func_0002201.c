nextBlank(FILE *input)
{
  wstring result = L"";

  while(true)
  {
    wint_t val = fgetwc(input);
    if(feof(input))
    {
      return L"";
    }
    switch(val)
    {
      case L'\\':
        fgetwc(input);
        break;
      case L'[':

        result = restOfBlank(input);
        return result;
    }
  }
}
