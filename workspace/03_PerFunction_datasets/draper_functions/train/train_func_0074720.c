GetOperandNumber(int currentIndex)
{
  int i, variableIndex = -1;

  if (isdigit(this->Function[currentIndex]) ||
     this->Function[currentIndex] == '.')
    {
    double *tempImmediates = new double[this->ImmediatesSize];
    for (i = 0; i < this->ImmediatesSize; i++)
      {
      tempImmediates[i] = this->Immediates[i];
      }
    if (this->Immediates)
      {
      delete [] this->Immediates;
      }


    this->Immediates = new double[this->ImmediatesSize + 1];


    for (i = 0; i < this->ImmediatesSize; i++)
      {
      this->Immediates[i] = tempImmediates[i];
      }

    this->Immediates[this->ImmediatesSize] =
      atof(&this->Function[currentIndex]);
    this->ImmediatesSize++;
    delete [] tempImmediates;
    return VTK_PARSER_IMMEDIATE;
    }

  if (!strncmp(&this->Function[currentIndex], "iHat", 4))
    {
    return VTK_PARSER_IHAT;
    }
  if (!strncmp(&this->Function[currentIndex], "jHat", 4))
    {
    return VTK_PARSER_JHAT;
    }
  if (!strncmp(&this->Function[currentIndex], "kHat", 4))
    {
    return VTK_PARSER_KHAT;
    }


  bool scalarVar = false;
  size_t currentLen = 0;


  for (i = 0; i < this->NumberOfScalarVariables; i++)
    {
    if (strncmp(&this->Function[currentIndex], this->ScalarVariableNames[i],
                strlen(this->ScalarVariableNames[i])) == 0)
      {
      if (variableIndex == -1 ||
          strlen(this->ScalarVariableNames[i]) > currentLen )
        {
        currentLen = strlen(this->ScalarVariableNames[i]);
        variableIndex = i;
        }
      }
    }
  if (variableIndex >= 0)
    {
    scalarVar = true;
    }

  for (i = 0; i < this->NumberOfVectorVariables; i++)
    {
    if (strncmp(&this->Function[currentIndex], this->VectorVariableNames[i],
                strlen(this->VectorVariableNames[i])) == 0)
      {
      if (variableIndex == -1
        || strlen(this->VectorVariableNames[i]) > currentLen )
        {
        scalarVar = false;
        currentLen = strlen(this->VectorVariableNames[i]);
        variableIndex = i;
        }
      }
    }
  if (variableIndex >= 0)
    {

    variableIndex = (scalarVar)?
      variableIndex:this->NumberOfScalarVariables + variableIndex;
    return static_cast<unsigned char>(
      VTK_PARSER_BEGIN_VARIABLES + variableIndex);
    }

  return 0;
}
