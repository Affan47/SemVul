net_in_expr(struct expr_t *ndp, struct net_t *np)
{
 struct net_t *np1;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID || ndp->optyp == GLBREF)
    {

     np1 = ndp->lu.sy->el.enp;
     if (np == np1) return(TRUE);
    }
   return(FALSE);
 }
 if (ndp->lu.x != NULL)
  { if (net_in_expr(ndp->lu.x, np)) return(TRUE); }
 if (ndp->ru.x != NULL)
  { if (net_in_expr(ndp->ru.x, np)) return(TRUE); }
 return(FALSE);
}
