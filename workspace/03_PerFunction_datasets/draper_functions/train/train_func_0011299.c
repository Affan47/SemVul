__lhsexpr_var_ndx(register struct expr_t *xp)
{
 switch ((byte) xp->optyp) {
  case GLBREF: case ID:
   break;
  case PARTSEL:

   break;
  case LSB:
   if (xp->ru.x->optyp == NUMBER || xp->ru.x->optyp == ISNUMBER) break;
   return(TRUE);
  case LCB:
   {
    register struct expr_t *catxp;

    for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
     {

      if (__lhsexpr_var_ndx(catxp->lu.x)) return(TRUE);
     }
   }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}
