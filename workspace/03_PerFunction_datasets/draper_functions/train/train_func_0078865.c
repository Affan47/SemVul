DestroyAttribute(void *attribute)
{
  register ImageAttribute
    *p;

  p=(ImageAttribute *) attribute;
  if (p->value != (char *) NULL)
    p->value=DestroyString(p->value);
  return(RelinquishMagickMemory(p));
}
