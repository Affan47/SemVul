chk_mixedsign_relops(struct expr_t *ndp)
{
 register struct expr_t *xp;

 switch ((byte) ndp->optyp) {
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM:
  case ID: case GLBREF:
   break;
  case LSB:
   if (chk_mixedsign_relops(ndp->ru.x)) return(TRUE);
   break;
  case PARTSEL:
   if (chk_mixedsign_relops(ndp->ru.x->lu.x)) return(TRUE);
   if (chk_mixedsign_relops(ndp->ru.x->ru.x)) return(TRUE);
   break;
  case LCB:
   {
    for (xp = ndp->ru.x; xp != NULL; xp = xp->ru.x)
     if (chk_mixedsign_relops(xp->lu.x)) return(TRUE);
   }
   break;
  case FCALL:
   {

    for (xp = ndp->ru.x; xp != NULL; xp = xp->ru.x)
     if (chk_mixedsign_relops(xp->lu.x)) return(TRUE);
   }
   break;
  default:
   if (ndp->lu.x != NULL) if (chk_mixedsign_relops(ndp->lu.x)) return(TRUE);
   if (ndp->ru.x != NULL) if (chk_mixedsign_relops(ndp->ru.x)) return(TRUE);
   switch ((byte) ndp->optyp) {
    case RELGE: case RELGT: case RELLE: case RELLT:

     if (ndp->lu.x->has_sign ^ ndp->ru.x->has_sign)
      {
       __sgfinform(440,
        "relational operator has mixed signed and word32 operands");
       return(TRUE);
      }
   }
 }
 return(FALSE);
}
