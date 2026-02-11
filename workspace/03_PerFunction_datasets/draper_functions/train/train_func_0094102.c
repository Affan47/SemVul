destroy_record_priority_queue()
{
  DBUG_ENTER("ha_partition::destroy_record_priority_queue");
  if (m_ordered_rec_buffer)
  {
    delete_queue(&m_queue);
    my_free(m_ordered_rec_buffer);
    m_ordered_rec_buffer= NULL;
  }
  DBUG_VOID_RETURN;
}
