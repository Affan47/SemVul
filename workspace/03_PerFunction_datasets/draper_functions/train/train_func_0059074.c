do_before_row_operations(TABLE *table)
{
  DBUG_ASSERT(m_memory == NULL);

  int error= 0;

  if (table->s->keys > 0)
  {
    m_memory= (uchar*) my_multi_malloc(MYF(MY_WME),
                                       &m_after_image,
                                       (uint) table->s->reclength,
                                       &m_key,
                                       (uint) table->key_info->key_length,
                                       NullS);
  }
  else
  {
    m_after_image= (uchar*) my_malloc(table->s->reclength, MYF(MY_WME));
    m_memory= m_after_image;
    m_key= NULL;
  }
  if (!m_memory)
    return HA_ERR_OUT_OF_MEM;

  table->timestamp_field_type= TIMESTAMP_NO_AUTO_SET;

  return error;
}
