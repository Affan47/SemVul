SetArraysWithDefault(const char* const* names,
                                                 int numArrays,
                                                 int defaultStatus)
{


  vtkDebugMacro("Settings arrays to given list of " << numArrays
                << " arrays.");


  vtkDataArraySelectionInternals* newInternal =
    new vtkDataArraySelectionInternals;

  newInternal->ArrayNames.reserve(numArrays);
  newInternal->ArraySettings.reserve(numArrays);


  int i;
  for(i=0;i < numArrays; ++i)
    {

    newInternal->ArrayNames.push_back(names[i]);


    int setting = defaultStatus?1:0;
    int index = this->GetArrayIndex(names[i]);
    if(index >= 0)
      {
      setting = this->Internal->ArraySettings[index];
      }
    newInternal->ArraySettings.push_back(setting);
    }


  delete this->Internal;
  this->Internal = newInternal;
}
