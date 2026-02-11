LtLoad(LtLight *li, char *name)
{
  IOBFILE *f;

  if(name == NULL || (f = iobfopen(name, "r")) == NULL) {
    OOGLError(1, "Can't find light file %s: %s", name, sperror());
    return NULL;
  }
  li = LtFLoad(li, f, name);
  iobfclose(f);
  return li;
}
