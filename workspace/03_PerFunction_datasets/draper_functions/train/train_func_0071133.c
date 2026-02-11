view_store_create_info(THD *thd, TABLE_LIST *table, String *buff)
{
  my_bool compact_view_name= TRUE;
  my_bool foreign_db_mode= (thd->variables.sql_mode & (MODE_POSTGRESQL |
                                                       MODE_ORACLE |
                                                       MODE_MSSQL |
                                                       MODE_DB2 |
                                                       MODE_MAXDB |
                                                       MODE_ANSI)) != 0;

  if (!thd->db || strcmp(thd->db, table->view_db.str))


    compact_view_name= table->compact_view_format= FALSE;
  else
  {


    TABLE_LIST *tbl;
    table->compact_view_format= TRUE;
    for (tbl= thd->lex->query_tables;
         tbl;
         tbl= tbl->next_global)
    {
      if (strcmp(table->view_db.str, tbl->view ? tbl->view_db.str :tbl->db)!= 0)
      {
        table->compact_view_format= FALSE;
        break;
      }
    }
  }

  buff->append(STRING_WITH_LEN("CREATE "));
  if (!foreign_db_mode)
  {
    view_store_options(thd, table, buff);
  }
  buff->append(STRING_WITH_LEN("VIEW "));
  if (!compact_view_name)
  {
    append_identifier(thd, buff, table->view_db.str, table->view_db.length);
    buff->append('.');
  }
  append_identifier(thd, buff, table->view_name.str, table->view_name.length);
  buff->append(STRING_WITH_LEN(" AS "));


  table->view->unit.print(buff, QT_ORDINARY);

  if (table->with_check != VIEW_CHECK_NONE)
  {
    if (table->with_check == VIEW_CHECK_LOCAL)
      buff->append(STRING_WITH_LEN(" WITH LOCAL CHECK OPTION"));
    else
      buff->append(STRING_WITH_LEN(" WITH CASCADED CHECK OPTION"));
  }
  return 0;
}
