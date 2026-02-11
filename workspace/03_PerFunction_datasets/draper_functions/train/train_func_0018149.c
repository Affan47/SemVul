toObjFile (int)
{
  Dsymbols *d = include (NULL, NULL);

  if (!d)
    return;

  for (size_t i = 0; i < d->dim; i++)
    {
      Dsymbol *s = (*d)[i];
      s->toObjFile (0);
    }
}
