GetMinElementType(struct FemType *data)
{
  int i,minelementtype;

  minelementtype = data->elementtypes[1];
  for(i=1;i<=data->noelements;i++)
    if(data->elementtypes[i] < minelementtype)
      minelementtype = data->elementtypes[i];

  return(minelementtype);
}
