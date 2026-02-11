expr_to_int(pIIR_Expression e, int &value, RegionStack &rstack)
{

  if (e->static_level != IR_LOCALLY_STATIC)
    return false;

  pIIR_Type base = get_base_type(e->subtype);
  pIIR_AbstractLiteralExpression ae = pIIR_AbstractLiteralExpression(e);
  if (base->is(IR_INTEGER_TYPE)) {
    string val_str;
    if (!emit_expr(e, val_str, rstack, DEFAULT))
      return false;
    value = atoi(val_str.c_str());
  } else if (base->is(IR_ENUMERATION_TYPE)) {
    string literal_str = pIIR_EnumerationLiteral(ae->value)->declarator->text.to_chars();
    value = literal_to_pos(pIIR_EnumerationType(base)->enumeration_literals, literal_str);
  } else

    return false;

  return true;
}
