get_field_value(char * name,
                    int no_of_fields, char * fieldname, char * value)
{
  char * v = get_field_string(name,no_of_fields, fieldname, value);
  if (v!=0) {
    return atoi(v);
  }
  return 0;
}
