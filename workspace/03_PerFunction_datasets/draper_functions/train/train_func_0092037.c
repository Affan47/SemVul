event_queue_element_compare_q(void *vptr, uchar* a, uchar *b)
{
  Event_queue_element *left = (Event_queue_element *)a;
  Event_queue_element *right = (Event_queue_element *)b;
  my_time_t lhs = left->execute_at;
  my_time_t rhs = right->execute_at;

  if (left->status == Event_parse_data::DISABLED)
    return right->status != Event_parse_data::DISABLED;

  if (right->status == Event_parse_data::DISABLED)
    return 1;

  return (lhs < rhs ? -1 : (lhs > rhs ? 1 : 0));
}
