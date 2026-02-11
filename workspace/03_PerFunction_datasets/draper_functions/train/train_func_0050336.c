inf_user_table_is_local(InfUser* user)
{

  if( (inf_user_get_flags(user) & INF_USER_LOCAL) == 0)
    return FALSE;
  if(inf_user_get_status(user) == INF_USER_UNAVAILABLE)
    return FALSE;

  return TRUE;
}
