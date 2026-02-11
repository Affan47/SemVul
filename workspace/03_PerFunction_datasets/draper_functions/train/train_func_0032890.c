clear_until_condition()
{
  DBUG_ENTER("clear_until_condition");

  until_condition= Relay_log_info::UNTIL_NONE;
  until_log_name[0]= 0;
  until_log_pos= 0;
  DBUG_VOID_RETURN;
}
