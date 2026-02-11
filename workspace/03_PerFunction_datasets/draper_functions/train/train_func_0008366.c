Lookup_previous(int code, const T_Lookup *lookup)
{
  int count;
  int current=-1;

  for(count=0; lookup[count].Label!=NULL; count++)
  {
    if (lookup[count].Code == code)
      current=count;
  }

  return lookup[(current + count - 1) % count].Code;
}
