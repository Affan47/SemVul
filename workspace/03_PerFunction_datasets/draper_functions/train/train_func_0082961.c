mysql_ha_close_table(THD *thd, TABLE_LIST *tables)
{

  if (tables->table && !tables->table->s->tmp_table)
  {

    tables->table->file->ha_index_or_rnd_end();
    tables->table->open_by_handler= 0;
    (void) close_thread_table(thd, &tables->table);
    thd->mdl_context.release_lock(tables->mdl_request.ticket);
  }
  else if (tables->table)
  {

    TABLE *table= tables->table;
    table->file->ha_index_or_rnd_end();
    table->query_id= thd->query_id;
    table->open_by_handler= 0;
    mark_tmp_table_for_reuse(table);
  }


  tables->table= NULL;

  tables->mdl_request.ticket= NULL;
}
