position(const uchar *record __attribute__ ((unused)))
{
  DBUG_ENTER("ha_federated::position");

  DBUG_ASSERT(stored_result);

  position_called= TRUE;

  memcpy(ref, &stored_result, sizeof(MYSQL_RES *));

  memcpy(ref + sizeof(MYSQL_RES *), &current_position,
               sizeof(MYSQL_ROW_OFFSET));
  DBUG_VOID_RETURN;
}
