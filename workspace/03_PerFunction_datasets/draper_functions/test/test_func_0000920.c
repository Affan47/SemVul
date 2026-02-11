SkipWhitespace(
  istream &infile, char linetext[256], char **cpp)
{
  char *cp = *cpp;

  while (infile.good())
    {

    while (isspace(*cp))
      {
      cp++;
      }

    if (*cp != '\0')
      {
      *cpp = cp;
      return 1;
      }

    this->ReadLine(infile, linetext);
    cp = linetext;
    }

  return 0;
}
