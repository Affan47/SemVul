myrg_status(MYRG_INFO *info,register MYMERGE_INFO *x,int flag)
{
  MYRG_TABLE *current_table;
  DBUG_ENTER("myrg_status");

  if (!(current_table = info->current_table) &&
      info->open_tables != info->end_table)
    current_table = info->open_tables;
  x->recpos  = info->current_table ?
    info->current_table->table->lastpos + info->current_table->file_offset :
      (ulong) -1L;
  if (flag != HA_STATUS_POS)
  {
    MYRG_TABLE *file;

    info->records=info->del=info->data_file_length=0;
    for (file=info->open_tables ; file != info->end_table ; file++)
    {
      file->file_offset=info->data_file_length;
      info->data_file_length+=file->table->s->state.state.data_file_length;
      info->records+=file->table->s->state.state.records;
      info->del+=file->table->s->state.state.del;
      DBUG_PRINT("info2",("table: %s, offset: %lu",
                  file->table->filename,(ulong) file->file_offset));
    }
    x->records= info->records;
    x->deleted= info->del;
    x->data_file_length= info->data_file_length;
    x->reclength= info->reclength;
    x->options= info->options;
    if (current_table)
    {


      x->errkey= current_table->table->errkey;


      x->dupp_key_pos= current_table->file_offset + current_table->table->dupp_key_pos;
    }
    else
    {
      x->errkey= 0;
      x->dupp_key_pos= 0;
    }
    x->rec_per_key = info->rec_per_key_part;
  }
  DBUG_RETURN(0);
}
