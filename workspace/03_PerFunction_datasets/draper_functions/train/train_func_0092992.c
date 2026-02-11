m_get_operator_type(pIIR_FunctionDeclaration fd)
{
  char *function_str = fd->declarator->text.to_chars();

  if (function_str[0] != '"')
    return NO_OP;

  char *libname = get_lib_name(fd->declarative_region);

  if (!strcmp(libname, "std") ||
      fd->is(IR_PREDEFINED_FUNCTION_DECLARATION))


    return STD_OP;
  else if (!strcmp(libname, "ieee"))

    return BASIC_OP;
  else
    return USER_OP;
}
