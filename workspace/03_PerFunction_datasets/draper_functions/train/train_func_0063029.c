shrink_array(struct column_info *ds,int npoints)
{
  int i;
  char **string2, *string;
  Array a,b;

  a = ds->array;

  string2 = (char**)DXAllocate(sizeof(char *) * npoints);
  for (i=0; i<npoints; i++) {
    DXExtractNthString((Object)a,i,&string);
    *(string2+i) = string;
  }
  b = (Array)DXMakeStringListV(npoints,string2);
  DXFree((Pointer)string2);
  DXDelete((Object)a);
  ds->array = b;

  return OK;
}
