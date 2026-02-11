print(String *str, enum_query_type query_type)
{
  if (engine)
  {
    str->append('(');
    engine->print(str, query_type);
    str->append(')');
  }
  else
    str->append("(...)");
}
