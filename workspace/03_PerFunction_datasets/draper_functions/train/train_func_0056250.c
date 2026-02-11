field_is_artificial (tree field)
{

  if (IDENTIFIER_POINTER (DECL_NAME (field)) [0] == '_')
    return true;


  if (DECL_INTERNAL_P (field))
    return true;

  return false;
}
