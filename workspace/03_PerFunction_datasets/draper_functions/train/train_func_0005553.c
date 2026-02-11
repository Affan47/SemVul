append_algorithm(TABLE_LIST *table, String *buff)
{
  buff->append(STRING_WITH_LEN("ALGORITHM="));
  switch ((int8)table->algorithm) {
  case VIEW_ALGORITHM_UNDEFINED:
    buff->append(STRING_WITH_LEN("UNDEFINED "));
    break;
  case VIEW_ALGORITHM_TMPTABLE:
    buff->append(STRING_WITH_LEN("TEMPTABLE "));
    break;
  case VIEW_ALGORITHM_MERGE:
    buff->append(STRING_WITH_LEN("MERGE "));
    break;
  default:
    DBUG_ASSERT(0);
  }
}
