make_list(n)
int n;
{object x =Cnil ;
  while (n-- > 0)
    x = make_cons(Cnil, x);
 return x;}
