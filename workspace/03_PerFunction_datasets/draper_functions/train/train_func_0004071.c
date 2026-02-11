change_table_name_in_triggers(THD *thd,
                                                   const char *old_db_name,
                                                   const char *new_db_name,
                                                   LEX_STRING *old_table_name,
                                                   LEX_STRING *new_table_name)
{
  char path_buff[FN_REFLEN];
  LEX_STRING *def, *on_table_name, new_def;
  ulong save_sql_mode= thd->variables.sql_mode;
  List_iterator_fast<LEX_STRING> it_def(definitions_list);
  List_iterator_fast<LEX_STRING> it_on_table_name(on_table_names_list);
  List_iterator_fast<ulonglong> it_mode(definition_modes_list);
  size_t on_q_table_name_len, before_on_len;
  String buff;

  DBUG_ASSERT(definitions_list.elements == on_table_names_list.elements &&
              definitions_list.elements == definition_modes_list.elements);

  while ((def= it_def++))
  {
    on_table_name= it_on_table_name++;
    thd->variables.sql_mode= (ulong) *(it_mode++);


    buff.length(0);


    DBUG_ASSERT(on_table_name->str > def->str);
    DBUG_ASSERT(on_table_name->str < (def->str + def->length));
    before_on_len= on_table_name->str - def->str;

    buff.append(def->str, before_on_len);
    buff.append(STRING_WITH_LEN("ON "));
    append_identifier(thd, &buff, new_table_name->str, new_table_name->length);
    buff.append(STRING_WITH_LEN(" "));
    on_q_table_name_len= buff.length() - before_on_len;
    buff.append(on_table_name->str + on_table_name->length,
                def->length - (before_on_len + on_table_name->length));


    new_def.str= (char*) memdup_root(&trigger_table->mem_root, buff.ptr(),
                                     buff.length());
    new_def.length= buff.length();
    on_table_name->str= new_def.str + before_on_len;
    on_table_name->length= on_q_table_name_len;
    *def= new_def;
  }

  thd->variables.sql_mode= save_sql_mode;

  if (thd->is_fatal_error)
    return TRUE;

  if (save_trigger_file(this, new_db_name, new_table_name->str))
    return TRUE;
  if (rm_trigger_file(path_buff, old_db_name, old_table_name->str))
  {
    (void) rm_trigger_file(path_buff, new_db_name, new_table_name->str);
    return TRUE;
  }
  return FALSE;
}
