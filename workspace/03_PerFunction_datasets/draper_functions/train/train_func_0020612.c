get_immediate_base_type(pIIR_Type type)
{
  if (type->declaration == NULL) {
    if (type->is(IR_ARRAY_SUBTYPE))
      type = ((pIIR_ArraySubtype)(type))->immediate_base;
    else if (type->is(IR_SCALAR_SUBTYPE))
      type = ((pIIR_ScalarSubtype)(type))->immediate_base;
  }

  return type;
}
