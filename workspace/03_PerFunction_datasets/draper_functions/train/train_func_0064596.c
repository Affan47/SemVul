ex_fun(char *fun, nodeType *p1)
{
  nodeType *p = NULL;

  if ( p1->type == typeVar )
    {
      p = ex_fun_var(fun, p1);
      if ( cdoVerbose ) printf("\t%s (%s)\n", fun, p1->u.var.nm);
    }
  else if ( p1->type == typeCon )
    {
      p = ex_fun_con(fun, p1);
      if ( cdoVerbose ) printf("\t%s (%g)\n", fun, p1->u.con.value);
    }
  else
    cdoAbort("Internal problem!");

  return (p);
}
