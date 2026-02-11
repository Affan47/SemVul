get_type_specifier (const type_p s)
{
  if (s->kind == TYPE_STRUCT)
    return "struct ";
  else if (s->kind == TYPE_LANG_STRUCT)
    return get_type_specifier (s->u.s.lang_struct);
  else if (s->kind == TYPE_UNION)
    return "union ";
  return "";
}
