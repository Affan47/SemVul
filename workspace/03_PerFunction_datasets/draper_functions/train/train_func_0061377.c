RemoveUGridNodeVariable(char *ugridVarName)
{
  int i;
  int maxVarNames = this->NumberOfNodeVariables;

  int idx = vtkModelMetadata::FindNameOnList(ugridVarName,
               this->NodeVariableNames, maxVarNames);

  if (idx == -1) return 1;

  delete []  this->NodeVariableNames[idx];

  for (i=idx+1; i<maxVarNames; i++)
    {
    int prev = i-1;

    this->NodeVariableNames[prev] = this->NodeVariableNames[i];
    this->NodeVariableNumberOfComponents[prev] =
         this->NodeVariableNumberOfComponents[i];
    this->MapToOriginalNodeVariableNames[prev] =
         this->MapToOriginalNodeVariableNames[i];
    }

  this->NodeVariableNames[maxVarNames-1] = NULL;

  this->NumberOfNodeVariables--;

  return 0;
}
