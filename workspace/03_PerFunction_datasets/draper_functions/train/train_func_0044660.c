parse_shop(void)
{
 int32 savi;
 struct expr_t *ndp, *rhsndp, *leftopndp;


 if ((leftopndp = parse_addop()) == NULL) return(NULL);
 ndp = __exprtab[__xndi];
 for (;;)
  {
   if (ndp->optyp == SHIFTL || ndp->optyp == SHIFTR
    || ndp->optyp == ASHIFTL || ndp->optyp == ASHIFTR)
    {
     savi = __xndi;
     __xndi++;
     if ((rhsndp = parse_addop()) == NULL) break;

     ndp = alloc_xtnd(savi);
     ndp->lu.x = leftopndp;
     ndp->ru.x = rhsndp;
     leftopndp = ndp;
     ndp = __exprtab[__xndi];
    }
   else break;
  }
 return(leftopndp);
}
