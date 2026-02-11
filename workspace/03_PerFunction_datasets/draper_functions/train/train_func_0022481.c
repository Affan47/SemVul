sql_strmake_with_convert(const char *str, size_t arg_length,
			       CHARSET_INFO *from_cs,
			       size_t max_res_length,
			       CHARSET_INFO *to_cs, size_t *result_length)
{
  char *pos;
  size_t new_length= to_cs->mbmaxlen*arg_length;
  max_res_length--;

  set_if_smaller(new_length, max_res_length);
  if (!(pos= (char*) sql_alloc(new_length+1)))
    return pos;

  if ((from_cs == &my_charset_bin) || (to_cs == &my_charset_bin))
  {

    new_length= min(arg_length, max_res_length);
    memcpy(pos, str, new_length);
  }
  else
  {
    uint dummy_errors;
    new_length= copy_and_convert((char*) pos, new_length, to_cs, str,
				 arg_length, from_cs, &dummy_errors);
  }
  pos[new_length]= 0;
  *result_length= new_length;
  return pos;
}
