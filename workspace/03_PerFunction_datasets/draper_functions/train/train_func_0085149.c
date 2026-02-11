SetScalarVariableValue(int i, double value)
{
  if (i < 0 || i >= this->NumberOfScalarVariables)
    {
    return;
    }

  if (this->ScalarVariableValues[i] != value)
    {
    this->ScalarVariableValues[i] = value;
    this->VariableMTime.Modified();
    }
  this->Modified();
}
