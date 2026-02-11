warn_if_overflow(int op_result)
{
  if (op_result == E_DEC_OVERFLOW)
  {
    set_warning(MYSQL_ERROR::WARN_LEVEL_WARN, ER_WARN_DATA_OUT_OF_RANGE, 1);
    return 1;
  }
  if (op_result == E_DEC_TRUNCATED)
  {
    set_warning(MYSQL_ERROR::WARN_LEVEL_NOTE, WARN_DATA_TRUNCATED, 1);

  }
  return 0;
}
