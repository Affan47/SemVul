set_user_connect(USER_CONN *uc)
{
  DBUG_ENTER("THD::set_user_connect");

  m_user_connect= uc;

  DBUG_VOID_RETURN;
}
