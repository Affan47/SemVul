get_declaration(pIIR_Type type)
{
  if ((type->declaration == NULL) &&
      (type->is(IR_SUBTYPE) && (implicit_subtype_declaration(pIIR_Subtype(type)) == NULL))) {
    if (type->is(IR_ARRAY_SUBTYPE)) {
      pIIR_ArraySubtype ast = pIIR_ArraySubtype(type);
      if (ast->immediate_base->declaration != NULL)
	return ast->immediate_base->declaration;
      else if (ast->immediate_base == ast)
	return get_declaration(ast->base);
      else
	return get_declaration(ast->immediate_base);

    } else if (type->is(IR_SCALAR_SUBTYPE)) {
      pIIR_ScalarSubtype sst = pIIR_ScalarSubtype(type);
      return get_declaration(sst->immediate_base);
    }
  }

  return type->declaration != NULL?
    type->declaration : implicit_subtype_declaration(pIIR_Subtype(type));
}
