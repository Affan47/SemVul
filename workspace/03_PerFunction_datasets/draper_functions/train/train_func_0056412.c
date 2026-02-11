conforming (pIIR_Declaration d1, pIIR_Declaration d2)
{
  if (d1->is(IR_SUBPROGRAM_DECLARATION))
    {
      if ((d1->is(IR_FUNCTION_DECLARATION)
	   && !d2->is(IR_FUNCTION_DECLARATION))
	  || (d1->is(IR_PROCEDURE_DECLARATION)
	      && !d2->is(IR_PROCEDURE_DECLARATION)))
	return false;

      pIIR_InterfaceList p1l =
	pIIR_SubprogramDeclaration(d1)->interface_declarations;
      pIIR_InterfaceList p2l =
	pIIR_SubprogramDeclaration(d2)->interface_declarations;

      while (p1l && p2l)
	{
	  pIIR_InterfaceDeclaration p1 = p1l->first;
	  pIIR_InterfaceDeclaration p2 = p2l->first;

	  if (p1->mode != p2->mode
	      || vaul_get_class (p1) != vaul_get_class (p2)
	      || p1->bus != p2->bus
	      || !same_type(p1->subtype, p2->subtype))
	    return false;
	  p1l = p1l->rest;
	  p2l = p2l->rest;
	}

      if (d1->is(IR_FUNCTION_DECLARATION))
	return same_type(pIIR_FunctionDeclaration(d1)->return_type,
			 pIIR_FunctionDeclaration(d2)->return_type);
      return true;
    }
  return false;
}
