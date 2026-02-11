print(String *str, enum_query_type query_type)
{
  str->append(STRING_WITH_LEN("make_set("));
  item->print(str, query_type);
  if (arg_count)
  {
    str->append(',');
    print_args(str, 0, query_type);
  }
  str->append(')');
}
