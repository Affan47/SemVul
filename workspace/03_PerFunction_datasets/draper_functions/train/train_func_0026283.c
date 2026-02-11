check_int(CHARSET_INFO *cs, const char *str, int length,
                         const char *int_end, int error)
{

  if (str == int_end || error == MY_ERRNO_EDOM)
  {
    ErrConvString err(str, length, cs);
    push_warning_printf(table->in_use, MYSQL_ERROR::WARN_LEVEL_WARN,
                        ER_TRUNCATED_WRONG_VALUE_FOR_FIELD,
                        ER(ER_TRUNCATED_WRONG_VALUE_FOR_FIELD),
                        "integer", err.ptr(), field_name,
                        (ulong) table->in_use->warning_info->current_row_for_warning());
    return 1;
  }

  if (test_if_important_data(cs, int_end, str + length))
  {
    set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, WARN_DATA_TRUNCATED, 1);
    return 2;
  }
  return 0;
}
