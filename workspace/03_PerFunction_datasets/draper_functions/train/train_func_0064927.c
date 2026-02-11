ConstructDimensions(vtkStdString *dimString,
    vtkFoamDict *dictPtr)
{
  if (!this->Parent->GetAddDimensionsToArrayNames())
    {
    return;
    }
  vtkFoamEntry *dimEntry = dictPtr->Lookup("dimensions");
  if (dimEntry != NULL && dimEntry->FirstValue().GetType() == vtkFoamToken::LABELLIST)
    {
    vtkIntArray &dims = dimEntry->LabelList();
    if (dims.GetNumberOfTuples() == 7)
      {
      int dimSet[7];
      for (int dimI = 0; dimI < 7; dimI++)
        {
        dimSet[dimI] = dims.GetValue(dimI);
        }
      static const char *units[7] =
      { "kg", "m", "s", "K", "mol", "A", "cd" };
      vtksys_ios::ostringstream posDim, negDim;
      int posSpc = 0, negSpc = 0;
      if (dimSet[0] == 1 && dimSet[1] == -1 && dimSet[2] == -2)
        {
        posDim << "Pa";
        dimSet[0] = dimSet[1] = dimSet[2] = 0;
        posSpc = 1;
        }
      for (int dimI = 0; dimI < 7; dimI++)
        {
        const int dimDim = dimSet[dimI];
        if (dimDim > 0)
          {
          if (posSpc)
            {
            posDim << " ";
            }
          posDim << units[dimI];
          if (dimDim > 1)
            {
            posDim << dimDim;
            }
          posSpc++;
          }
        else if (dimDim < 0)
          {
          if (negSpc)
            {
            negDim << " ";
            }
          negDim << units[dimI];
          if (dimDim < -1)
            {
            negDim << -dimDim;
            }
          negSpc++;
          }
        }
      *dimString += " [" + posDim.str();
      if (negSpc > 0)
        {
        if (posSpc == 0)
          {
          *dimString += "1";
          }
        if (negSpc > 1)
          {
          *dimString += "/(" + negDim.str() + ")";
          }
        else
          {
          *dimString += "/" + negDim.str();
          }
        }
      else if (posSpc == 0)
        {
        *dimString += "-";
        }
      *dimString += "]";
      }
    }
}
