PolyListDelete(PolyList *pl)
{
  int i;
  Poly *p;

  if (pl == NULL) {
    return NULL;
  }

  if((p = pl->p) != NULL) {
    for(i = pl->n_polys; --i >= 0; p++) {
      if(p->v != NULL) OOGLFree(p->v);
    }
    OOGLFree(pl->p);
  }
  if(pl->vl != NULL) {
    OOGLFree(pl->vl);
  }

  PolyListDelete(pl->plproj);

  return NULL;
}
