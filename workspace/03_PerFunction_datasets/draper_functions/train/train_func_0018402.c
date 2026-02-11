allocComplexFieldIndex (void)
{
  ComplexFieldIndex res;

  if (emptyEnt != NULL)
    {
      res = emptyEnt;
      emptyEnt = NULL;
    }
  else
    {
      res = (ComplexFieldIndex) xmalloc (sizeof (struct complex_field_index));
    }
  return res;
}
