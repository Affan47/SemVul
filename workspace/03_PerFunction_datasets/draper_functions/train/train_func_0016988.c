print(String *str, enum_query_type query_type)
{
  char *end= (char*) str_value.ptr() + str_value.length(),
       *ptr= end - min(str_value.length(), sizeof(longlong));
  str->append("0x");
  for (; ptr != end ; ptr++)
  {
    str->append(_dig_vec_lower[((uchar) *ptr) >> 4]);
    str->append(_dig_vec_lower[((uchar) *ptr) & 0x0F]);
  }
}
