AddOperation(const char* operationType,
                                     const char* name,
                                     const char* fromFieldLoc,
                                     const char* toFieldLoc)
{
  int numAttr = vtkDataSetAttributes::NUM_ATTRIBUTES;
  int numOpTypes = 2;
  int numFieldLocs = 3;
  int opType=-1, i;

  for(i=0; i<numOpTypes; i++)
    {
    if (!strcmp(operationType, OperationTypeNames[i]))
      {
      opType = i;
      break;
      }
    }
  if (opType == -1)
    {
    vtkErrorMacro("Syntax error in operation.");
    return -1;
    }
  int attributeType=-1;
  for(i=0; i<numAttr; i++)
    {
    if (!strcmp(name, AttributeNames[i]))
      {
      attributeType = i;
      break;
      }
    }

  int fromLoc=-1;
  for(i=0; i<numFieldLocs; i++)
    {
    if (!strcmp(fromFieldLoc, FieldLocationNames[i]))
      {
      fromLoc = i;
      break;
      }
    }
  if (fromLoc == -1)
    {
    vtkErrorMacro("Syntax error in operation.");
    return -1;
    }

  int toLoc=-1;
  for(i=0; i<numFieldLocs; i++)
    {
    if (!strcmp(toFieldLoc, FieldLocationNames[i]))
      {
      toLoc = i;
      break;
      }
    }
  if (toLoc == -1)
    {
    vtkErrorMacro("Syntax error in operation.");
    return -1;
    }

  if ( attributeType == -1 )
    {
    vtkDebugMacro("Adding operation with parameters: "
                  << opType << " " << name << " "
                  << fromLoc << " " << toLoc);
    return this->AddOperation(opType, name, fromLoc, toLoc);
    }
  else
    {
    vtkDebugMacro("Adding operation with parameters: "
                  << opType << " " << attributeType << " "
                  << fromLoc << " " << toLoc);
    return this->AddOperation(opType, attributeType, fromLoc, toLoc);
    }
}
