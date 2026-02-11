dbltest(void        (*oper) (), value * lval1, value * lval2)
{
   if ((oper != ob_add) && (oper != ob_sub))
      return 0;
   if (lval1->ident != iARRAY)
      return 0;
   if (lval2->ident == iARRAY)
      return 0;
   return sizeof(cell) / 2;
}
