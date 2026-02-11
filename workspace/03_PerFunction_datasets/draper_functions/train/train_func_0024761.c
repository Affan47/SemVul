init_one_value(const struct my_option *option, void *variable,
			   longlong value)
{
  DBUG_ENTER("init_one_value");
  switch ((option->var_type & GET_TYPE_MASK)) {
  case GET_BOOL:
    *((my_bool*) variable)= (my_bool) value;
    break;
  case GET_INT:
    *((int*) variable)= (int) getopt_ll_limit_value((int) value, option, NULL);
    break;
  case GET_ENUM:
    *((ulong*) variable)= (ulong) value;
    break;
  case GET_UINT:
    *((uint*) variable)= (uint) getopt_ull_limit_value((uint) value, option, NULL);
    break;
  case GET_LONG:
    *((long*) variable)= (long) getopt_ll_limit_value((long) value, option, NULL);
    break;
  case GET_ULONG:
    *((ulong*) variable)= (ulong) getopt_ull_limit_value((ulong) value, option, NULL);
    break;
  case GET_LL:
    *((longlong*) variable)= (longlong) getopt_ll_limit_value((longlong) value, option, NULL);
    break;
  case GET_ULL:
    *((ulonglong*) variable)= (ulonglong) getopt_ull_limit_value((ulonglong) value, option, NULL);
    break;
  case GET_SET:
  case GET_FLAGSET:
    *((ulonglong*) variable)= (ulonglong) value;
    break;
  case GET_DOUBLE:
    *((double*) variable)= getopt_ulonglong2double(value);
    break;
  case GET_STR:


    if ((char*) (intptr) value)
      *((char**) variable)= (char*) (intptr) value;
    break;
  case GET_STR_ALLOC:


    if ((char*) (intptr) value)
    {
      char **pstr= (char **) variable;
      my_free(*pstr);
      *pstr= my_strdup((char*) (intptr) value, MYF(MY_WME));
    }
    break;
  default:
    break;
  }
  DBUG_VOID_RETURN;
}
