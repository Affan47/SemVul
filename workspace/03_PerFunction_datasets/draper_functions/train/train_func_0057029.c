cdfg_create_default_instance(pIIR_Type type, RegionStack &rstack)
{
  string str;
  pIIR_Type im_base_type = get_immediate_base_type(type);
  pIIR_TypeDeclaration type_decl = get_declaration(type);


  str += "(create-object " + get_escaped_string(get_long_name(type_decl)) + ")";

  return str;
}
