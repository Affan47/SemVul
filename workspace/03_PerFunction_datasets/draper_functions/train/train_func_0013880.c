Assign(const char* name,
                                const char* attributeType,
                                const char* attributeLoc)
{
  if (!name || !attributeType || !attributeLoc)
    {
    return;
    }

  int numAttr = vtkDataSetAttributes::NUM_ATTRIBUTES;
  int numAttributeLocs = vtkAssignAttribute::NUM_ATTRIBUTE_LOCS;
  int i;


  int inputAttributeType=-1;
  for(i=0; i<numAttr; i++)
    {
    if (!strcmp(name, AttributeNames[i]))
      {
      inputAttributeType = i;
      break;
      }
    }

  int attrType=-1;
  for(i=0; i<numAttr; i++)
    {
    if (!strcmp(attributeType, AttributeNames[i]))
      {
      attrType = i;
      break;
      }
    }
  if ( attrType == -1 )
    {
    vtkErrorMacro("Target attribute type is invalid.");
    return;
    }

  int loc=-1;
  for(i=0; i<numAttributeLocs; i++)
    {
    if (!strcmp(attributeLoc, AttributeLocationNames[i]))
      {
      loc = i;
      break;
      }
    }
  if (loc == -1)
    {
    vtkErrorMacro("Target location for the attribute is invalid.");
    return;
    }

  if ( inputAttributeType == -1 )
    {
    this->Assign(name, attrType, loc);
    }
  else
    {
    this->Assign(inputAttributeType, attrType, loc);
    }
}
