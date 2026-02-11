init_definer(THD *thd)
{
  DBUG_ENTER("Event_parse_data::init_definer");

  DBUG_ASSERT(thd->lex->definer);

  const char *definer_user= thd->lex->definer->user.str;
  const char *definer_host= thd->lex->definer->host.str;
  size_t  definer_user_len= thd->lex->definer->user.length;
  size_t  definer_host_len= thd->lex->definer->host.length;

  DBUG_PRINT("info",("init definer_user thd->mem_root: 0x%lx  "
                     "definer_user: 0x%lx", (long) thd->mem_root,
                     (long) definer_user));


  DBUG_PRINT("info",("init definer as whole"));
  definer.length= definer_user_len + definer_host_len + 1;
  definer.str= (char*) thd->alloc(definer.length + 1);

  DBUG_PRINT("info",("copy the user"));
  memcpy(definer.str, definer_user, definer_user_len);
  definer.str[definer_user_len]= '@';

  DBUG_PRINT("info",("copy the host"));
  memcpy(definer.str + definer_user_len + 1, definer_host, definer_host_len);
  definer.str[definer.length]= '\0';
  DBUG_PRINT("info",("definer [%s] initted", definer.str));

  DBUG_VOID_RETURN;
}
