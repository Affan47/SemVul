print(String *str, enum_query_type query_type)
{
  if (arg_count == 1)
  {
    Item_func::print(str, query_type);
    return;
  }
  str->append(Item_func_trim::func_name());
  str->append('(');
  str->append(mode_name());
  str->append(' ');
  args[1]->print(str, query_type);
  str->append(STRING_WITH_LEN(" from "));
  args[0]->print(str, query_type);
  str->append(')');
}
