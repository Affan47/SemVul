regcomp(bool send_error)
{
  char buff[MAX_FIELD_WIDTH];
  String tmp(buff,sizeof(buff),&my_charset_bin);
  String *res= args[1]->val_str(&tmp);
  int error;

  if (args[1]->null_value)
    return -1;

  if (regex_compiled)
  {
    if (!stringcmp(res, &prev_regexp))
      return 0;
    prev_regexp.copy(*res);
    my_regfree(&preg);
    regex_compiled= 0;
  }

  if (cmp_collation.collation != regex_lib_charset)
  {

    uint dummy_errors;
    if (conv.copy(res->ptr(), res->length(), res->charset(),
                  regex_lib_charset, &dummy_errors))
      return 1;
    res= &conv;
  }

  if ((error= my_regcomp(&preg, res->c_ptr_safe(),
                         regex_lib_flags, regex_lib_charset)))
  {
    if (send_error)
    {
      (void) my_regerror(error, &preg, buff, sizeof(buff));
      my_error(ER_REGEXP_ERROR, MYF(0), buff);
    }
    return 1;
  }
  regex_compiled= 1;
  return 0;
}
