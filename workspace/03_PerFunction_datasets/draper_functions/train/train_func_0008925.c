_nc_Make_Argument(const FIELDTYPE *typ, va_list *ap, int *err)
{
  TypeArgument *res = (TypeArgument *)0;
  TypeArgument *p;

  if (typ != 0 && (typ->status & _HAS_ARGS) != 0)
    {
      assert(err != 0 && ap != (va_list *)0);
      if ((typ->status & _LINKED_TYPE) != 0)
	{
	  p = typeMalloc(TypeArgument, 1);

	  if (p != 0)
	    {
	      p->left = _nc_Make_Argument(typ->left, ap, err);
	      p->right = _nc_Make_Argument(typ->right, ap, err);
	      return p;
	    }
	  else
	    {
	      *err += 1;
	    }
	}
      else
	{
	  assert(typ->makearg != (void *)0);
	  if (!(res = (TypeArgument *)typ->makearg(ap)))
	    {
	      *err += 1;
	    }
	}
    }
  return res;
}
