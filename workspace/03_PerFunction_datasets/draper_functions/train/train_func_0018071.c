_gtr_msg_new (po_message_iterator_t iter, po_message_t message)
{
  GtrMsg *msg;

  g_return_val_if_fail (iter != NULL || message != NULL, NULL);

  msg = g_object_new (GTR_TYPE_MSG, NULL);

  _gtr_msg_set_iterator (msg, iter);
  _gtr_msg_set_message (msg, message);


  if (gtr_msg_is_fuzzy (msg))
    gtr_msg_set_status (msg, GTR_MSG_STATUS_FUZZY);
  else if (gtr_msg_is_translated (msg))
    gtr_msg_set_status (msg, GTR_MSG_STATUS_TRANSLATED);
  else
    gtr_msg_set_status (msg, GTR_MSG_STATUS_UNTRANSLATED);

  return msg;
}
