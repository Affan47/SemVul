lhsexpr_hassym(struct expr_t *ndp, struct sy_t *syp)
{
 register struct expr_t *ndp2;

 switch ((byte) ndp->optyp) {
   case ID:
    if (ndp->lu.sy == syp) return(TRUE);
    break;
   case GLBREF: case NUMBER: case REALNUM: break;
   case LSB: case PARTSEL:
    if (ndp->lu.x->lu.sy == syp) return(TRUE);
    break;
   case LCB:

    for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {

      if (ndp2->lu.x->lu.sy == syp) return(TRUE);
     }
    break;
   default: __case_terr(__FILE__, __LINE__);
  }
 return(FALSE);
}
