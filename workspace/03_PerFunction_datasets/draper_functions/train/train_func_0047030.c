__to_glbcmp_nam(struct expr_t *gcmp_ndp)
{
 char *chp;

 if (gcmp_ndp->lu.x->optyp == XMRID) chp = gcmp_ndp->lu.x->ru.qnchp;
 else if (gcmp_ndp->lu.x->optyp == LSB || gcmp_ndp->lu.x->optyp == PARTSEL)
  chp = gcmp_ndp->lu.x->lu.x->ru.qnchp;
 else { __case_terr(__FILE__, __LINE__); return(NULL); }
 return(chp);
}
