OdFree(order **od)
{
  order *r;

  if (*od) {
    r=*od;
    iFree(&r->adjn);
    iFree(&r->rbeg);
    iFree(&r->rexs);
    iFree(&r->rlen);
    iFree(&r->rend);
    iFree(&r->pres);
    iFree(&r->succ);
    free(*od);
    *od=NULL;
  }
}
