check_locale(sys_var *self, THD *thd, set_var *var)
{
  if (!var->value)
    return false;

  MY_LOCALE *locale;
  char buff[STRING_BUFFER_USUAL_SIZE];
  if (var->value->result_type() == INT_RESULT)
  {
    int lcno= (int)var->value->val_int();
    if (!(locale= my_locale_by_number(lcno)))
    {
      my_error(ER_UNKNOWN_LOCALE, MYF(0), llstr(lcno, buff));
      return true;
    }
    if (check_not_null(self, thd, var))
      return true;
  }
  else
  {
    String str(buff, sizeof(buff), system_charset_info), *res;
    if (!(res=var->value->val_str(&str)))
      return true;
    else if (!(locale= my_locale_by_name(res->c_ptr_safe())))
    {
      ErrConvString err(res);
      my_error(ER_UNKNOWN_LOCALE, MYF(0), err.ptr());
      return true;
    }
  }

  var->save_result.ptr= locale;

  if (!locale->errmsgs->errmsgs)
  {
    mysql_mutex_lock(&LOCK_error_messages);
    if (!locale->errmsgs->errmsgs &&
        read_texts(ERRMSG_FILE, locale->errmsgs->language,
                   &locale->errmsgs->errmsgs,
                   ER_ERROR_LAST - ER_ERROR_FIRST + 1))
    {
      push_warning_printf(thd, MYSQL_ERROR::WARN_LEVEL_WARN, ER_UNKNOWN_ERROR,
                          "Can't process error message file for locale '%s'",
                          locale->name);
      mysql_mutex_unlock(&LOCK_error_messages);
      return true;
    }
    mysql_mutex_unlock(&LOCK_error_messages);
  }
  return false;
}
