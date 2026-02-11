push_warning(THD *thd, const MYSQL_ERROR *sql_condition)
{
  MYSQL_ERROR *new_condition= push_warning(thd,
                                           sql_condition->get_sql_errno(),
                                           sql_condition->get_sqlstate(),
                                           sql_condition->get_level(),
                                           sql_condition->get_message_text());

  if (new_condition)
    new_condition->copy_opt_attributes(sql_condition);

  return new_condition;
}
