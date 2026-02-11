xhas_multconn_wire(struct expr_t *ndp)
{
 struct expr_t *ndp2;
 struct net_t *np;

 switch ((byte) ndp->optyp) {
  case ID:
   np = ndp->lu.sy->el.enp;
chk_mult:
   if (np->nu.ct->num_prtconns == 2) return(TRUE);
   break;
  case PARTSEL: case LSB:
   np = ndp->lu.x->lu.sy->el.enp;
   goto chk_mult;
  case LCB:
   for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    { if (xhas_multconn_wire(ndp2->lu.x)) return(TRUE); }
   break;
  case OPEMPTY: break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}
