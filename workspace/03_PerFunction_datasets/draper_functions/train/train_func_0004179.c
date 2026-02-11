GeomGet(Geom *g, int attr, void *attrp)
{
  if(g == NULL)
    return -1;

  switch(attr) {
  case CR_APPEAR:
    *(Appearance **)attrp = g->ap;
    break;
#if 0
  case CR_HANDLE:
    *(Handle **)attrp = g->handle;
    break;
#endif
  default:
    if(g->Class->get)
      return (*g->Class->get)(g, attr, attrp);
  }
  return 0;
}
