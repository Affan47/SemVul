recalculate_activation_times(THD *thd)
{
  uint i;
  DBUG_ENTER("Event_queue::recalculate_activation_times");

  LOCK_QUEUE_DATA();
  DBUG_PRINT("info", ("%u loaded events to be recalculated", queue.elements));
  for (i= 0; i < queue.elements; i++)
  {
    ((Event_queue_element*)queue_element(&queue, i))->compute_next_execution_time();
  }
  queue_fix(&queue);


  for (i= queue.elements; i > 0; i--)
  {
    Event_queue_element *element = (Event_queue_element*)queue_element(&queue, i - 1);
    if (element->status != Event_parse_data::DISABLED)
      break;


    queue_remove(&queue, i - 1);
    delete element;
  }
  UNLOCK_QUEUE_DATA();


  DBUG_VOID_RETURN;
}
