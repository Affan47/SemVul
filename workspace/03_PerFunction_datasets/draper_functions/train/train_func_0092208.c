calc_tmp_field_type(enum enum_field_types table_field_type,
                    Item_result result_type)
{

  switch (result_type) {
  case STRING_RESULT:
  case REAL_RESULT:
    if (table_field_type != MYSQL_TYPE_FLOAT)
      table_field_type= MYSQL_TYPE_DOUBLE;
    break;
  case INT_RESULT:
    table_field_type= MYSQL_TYPE_LONGLONG;

  case DECIMAL_RESULT:
    if (table_field_type != MYSQL_TYPE_LONGLONG)
      table_field_type= MYSQL_TYPE_NEWDECIMAL;
    break;
  case ROW_RESULT:
  default:
    DBUG_ASSERT(0);
  }
  return table_field_type;
}
