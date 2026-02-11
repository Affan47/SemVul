ComputeRequiredArrays(
  vtkDataSetAttributes* pd, int ctype)
{
  if ((ctype < COPYTUPLE) || (ctype > PASSDATA))
    {
    vtkErrorMacro("Must call compute required with COPYTUPLE, INTERPOLATE or PASSDATA");
    ctype = COPYTUPLE;
    }


  int* copyFlags = new int[pd->GetNumberOfArrays()];
  int index, i, numArrays = 0;
  for(i=0; i<pd->GetNumberOfArrays(); i++)
    {
    const char* arrayName = pd->GetArrayName(i);


    if ( (this->GetFlag(arrayName) != 0) &&
         !(this->DoCopyAllOff && (this->GetFlag(arrayName) != 1)) &&
         pd->GetAbstractArray(i))
      {

      if (ctype != INTERPOLATE ||
          !pd->GetAbstractArray(i)->IsA("vtkIdTypeArray"))
        {
        copyFlags[numArrays] = i;
        numArrays++;
        }
      }
    }


  int alreadyCopied;
  int attributeType, j;
  for(attributeType=0; attributeType<NUM_ATTRIBUTES; attributeType++)
    {
    index = pd->AttributeIndices[attributeType];
    int flag = this->GetFlag(pd->GetArrayName(index));

    if (this->CopyAttributeFlags[ctype][attributeType] && flag)
      {


      if (pd->GetArray(index))
        {
        alreadyCopied = 0;
        for(i=0; i<numArrays; i++)
          {
          if ( index == copyFlags[i] )
            {
            alreadyCopied = 1;
            }
          }

        if (!alreadyCopied)
          {

          if (ctype != INTERPOLATE ||
              !pd->GetArray(index)->IsA("vtkIdTypeArray"))
            {
            copyFlags[numArrays] = index;
            numArrays++;
            }
          }
        }
      }


    else
      {
      for(i=0; i<numArrays; i++)
        {
        if ( index == copyFlags[i] )
          {
          for(j=i; j<numArrays-1; j++)
            {
            copyFlags[j] = copyFlags[j+1];
            }
          numArrays--;
          i--;
          }
        }
      }
    }

  vtkFieldData::BasicIterator it(copyFlags, numArrays);
  delete[] copyFlags;
  return it;
}
