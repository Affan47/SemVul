RemoveCoordinateScalarVariables()
{
  int i;

  for (i = 0; i < this->NumberOfCoordinateScalarArrays; i++)
    {
    delete [] this->CoordinateScalarVariableNames[i];
    this->CoordinateScalarVariableNames[i] = NULL;
    }
  if (this->NumberOfCoordinateScalarArrays > 0)
    {
    delete [] this->CoordinateScalarVariableNames;
    this->CoordinateScalarVariableNames = NULL;
    delete [] this->SelectedCoordinateScalarComponents;
    this->SelectedCoordinateScalarComponents = NULL;
    }
  this->NumberOfCoordinateScalarArrays = 0;

  this->FunctionParser->RemoveScalarVariables();
}
