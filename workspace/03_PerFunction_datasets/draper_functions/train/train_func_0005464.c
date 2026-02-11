GetVariableNameLength(int variableNumber)
{
  if (variableNumber < this->NumberOfScalarVariables)
    {
    return static_cast<int>(strlen(this->ScalarVariableNames[variableNumber]));
    }
  else
    {
    return static_cast<int>(strlen(
      this->VectorVariableNames[variableNumber -
                               this->NumberOfScalarVariables]));
    }
}
