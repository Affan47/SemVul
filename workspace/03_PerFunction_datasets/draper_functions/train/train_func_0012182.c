zx_DEC_ELEM_demomed_ObjectSearchParm(struct zx_ctx* c, struct zx_demomed_ObjectSearchParm_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_demomed_Dir_ELEM:
    if (!x->Dir)
      x->Dir = el;
    return 1;
  case zx_demomed_Name_ELEM:
    if (!x->Name)
      x->Name = el;
    return 1;
  case zx_demomed_Type_ELEM:
    if (!x->Type)
      x->Type = el;
    return 1;
  case zx_demomed_objectID_ELEM:
    if (!x->objectID)
      x->objectID = el;
    return 1;

  default: return 0;
  }
}
