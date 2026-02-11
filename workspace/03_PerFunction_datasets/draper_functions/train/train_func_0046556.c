check_associations(pIIR_AssociationList assoc_list, pIIR_InterfaceList interface_list, RegionStack &rstack)
{
  int error_count = 0;


  for (pIIR_InterfaceList il = interface_list; il; il = il->rest)
    {


      pIIR_InterfaceDeclaration decl = il->first;
      list<pIIR_AssociationElement> formal_assoc;
      for (pIIR_AssociationList al = assoc_list; al; al = al->rest)
	if (al->first->formal_declaration == decl)
	  formal_assoc.push_back(al->first);

      error_count += check_association(assoc_list, formal_assoc, decl, rstack);
    }

  return error_count;
}
