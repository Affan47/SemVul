Lookup_next(int code, const T_Lookup *lookup)
{
  int i;

  for(i=0; lookup[i].Label!=NULL; i++)
  {
    if (lookup[i].Code == code)
    {
      if (lookup[i+1].Label==NULL)
        return lookup[0].Code;
      return lookup[i+1].Code;
    }
  }
  return 0;
}
