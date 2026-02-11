update_queue_push(uq_callback_t callback,
                                     struct update_queue_data *uq_data)
{
  update_queue_hash_replace(update_queue, callback, uq_data);

  if (!update_queue_has_idle_callback
      && !update_queue_is_frozen()) {
    update_queue_has_idle_callback = TRUE;
    add_idle_callback(update_unqueue, NULL);
  }
}
