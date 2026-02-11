execute_direct(LEX_STRING sql_text)
{
  Execute_sql_statement execute_sql_statement(sql_text);
  DBUG_PRINT("ed_query", ("%s", sql_text.str));

  return execute_direct(&execute_sql_statement);
}
