check_duplicates_in_interval(const char *set_or_name,
                                  const char *name, TYPELIB *typelib,
                                  CHARSET_INFO *cs, unsigned int *dup_val_count)
{
  TYPELIB tmp= *typelib;
  const char **cur_value= typelib->type_names;
  unsigned int *cur_length= typelib->type_lengths;
  *dup_val_count= 0;

  for ( ; tmp.count > 1; cur_value++, cur_length++)
  {
    tmp.type_names++;
    tmp.type_lengths++;
    tmp.count--;
    if (find_type2(&tmp, (const char*)*cur_value, *cur_length, cs))
    {
      THD *thd= current_thd;
      ErrConvString err(*cur_value, *cur_length, cs);
      if ((current_thd->variables.sql_mode &
         (MODE_STRICT_TRANS_TABLES | MODE_STRICT_ALL_TABLES)))
      {
        my_error(ER_DUPLICATED_VALUE_IN_TYPE, MYF(0),
                 name, err.ptr(), set_or_name);
        return 1;
      }
      push_warning_printf(thd,MYSQL_ERROR::WARN_LEVEL_NOTE,
                          ER_DUPLICATED_VALUE_IN_TYPE,
                          ER(ER_DUPLICATED_VALUE_IN_TYPE),
                          name, err.ptr(), set_or_name);
      (*dup_val_count)++;
    }
  }
  return 0;
}
