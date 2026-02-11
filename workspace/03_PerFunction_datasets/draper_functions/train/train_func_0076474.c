sp_load_for_information_schema(THD *thd, TABLE *proc_table, String *db,
                               String *name, ulong sql_mode, int type,
                               const char *returns, const char *params,
                               bool *free_sp_head)
{
  const char *sp_body;
  String defstr;
  struct st_sp_chistics sp_chistics;
  const LEX_STRING definer_user= {(char*)STRING_WITH_LEN("")};
  const LEX_STRING definer_host= {(char*)STRING_WITH_LEN("")};
  LEX_STRING sp_db_str;
  LEX_STRING sp_name_str;
  sp_head *sp;
  sp_cache **spc= ((type == TYPE_ENUM_PROCEDURE) ?
                  &thd->sp_proc_cache : &thd->sp_func_cache);
  sp_db_str.str= db->c_ptr();
  sp_db_str.length= db->length();
  sp_name_str.str= name->c_ptr();
  sp_name_str.length= name->length();
  sp_name sp_name_obj(sp_db_str, sp_name_str, true);
  sp_name_obj.init_qname(thd);
  *free_sp_head= 0;
  if ((sp= sp_cache_lookup(spc, &sp_name_obj)))
  {
    return sp;
  }

  LEX *old_lex= thd->lex, newlex;
  Stored_program_creation_ctx *creation_ctx=
    Stored_routine_creation_ctx::load_from_db(thd, &sp_name_obj, proc_table);
  sp_body= (type == TYPE_ENUM_FUNCTION ? "RETURN NULL" : "BEGIN END");
  bzero((char*) &sp_chistics, sizeof(sp_chistics));
  defstr.set_charset(creation_ctx->get_client_cs());
  if (!create_string(thd, &defstr, type,
                     sp_db_str.str, sp_db_str.length,
                     sp_name_obj.m_name.str, sp_name_obj.m_name.length,
                     params, strlen(params),
                     returns, strlen(returns),
                     sp_body, strlen(sp_body),
                     &sp_chistics, &definer_user, &definer_host, sql_mode))
    return 0;

  thd->lex= &newlex;
  newlex.current_select= NULL;
  sp= sp_compile(thd, &defstr, sql_mode, creation_ctx);
  *free_sp_head= 1;
  thd->lex->sphead= NULL;
  lex_end(thd->lex);
  thd->lex= old_lex;
  return sp;
}
