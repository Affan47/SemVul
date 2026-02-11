ParseInvertFlagValue(
  istream &infile, char linetext[256], char **cpp, int *invertFlag)
{
  char data[256];

  if (!this->ParseStringValue(infile, linetext, cpp, data))
    {
    return 0;
    }
  if (strcmp(data, "False") == 0)
    {
    *invertFlag = 0;
    }
  else if (strcmp(data, "True") == 0)
    {
    *invertFlag = 1;
    }
  else
    {
    vtkErrorMacro("Invert_Flag must be \'True\' or \'False\' "
                  << this->FileName << ":" << this->LineNumber);
    return 0;
    }

  return 1;
}
