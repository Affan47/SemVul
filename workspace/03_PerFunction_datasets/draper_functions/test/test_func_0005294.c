__get_const_bselndx(register struct expr_t *ndp)
{
 register int32 biti;
 register word32 *wp;


 if (ndp->ru.x->optyp == NUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else if (ndp->ru.x->optyp == ISNUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   wp = &(wp[2*__inum]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else { __case_terr(__FILE__, __LINE__); biti = -1; }
 return(biti);
}
