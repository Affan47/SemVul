m_check_expression(pIIR_SimpleReference sr, RegionStack &rstack)
{
  pIIR_ObjectDeclaration decl = sr->object;


  if (decl->is(IR_CONSTANT_DECLARATION)) {
      if (valid_folded_value(sr))
	static_declarative_region(sr) = RootDeclarativeRegion(rstack);
      else if (pIIR_ConstantDeclaration(decl)->initial_value != NULL)
	static_declarative_region(sr) =
	  static_declarative_region(pIIR_ConstantDeclaration(decl)->initial_value);
      else
	static_declarative_region(sr) = RootDeclarativeRegion(rstack);

  } else if (decl->is(IR_CONSTANT_INTERFACE_DECLARATION)) {
    static_declarative_region(sr) = static_declarative_region(decl);

  } else
    static_declarative_region(sr) = NULL;

  return 0;
}
