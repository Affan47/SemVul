event_callback(guestfs_h *g, void *opaque,
               uint64_t event, int event_handle,
               int flags,
               const char *buf, size_t buf_len,
               const uint64_t *array, size_t array_len)
{
  GuestfsSessionEventParams *params = g_slice_new0(GuestfsSessionEventParams);

  params->event = guestfs_session_event_from_guestfs_event(event);
  params->flags = flags;

  params->buf = g_byte_array_sized_new(buf_len);
  g_byte_array_append(params->buf, buf, buf_len);

  for(size_t i = 0; i < array_len && i < 4; i++) {
    if(array_len > 4) {
      array_len = 4;
    }
    memcpy(params->array, array, sizeof(array[0]) * array_len);
  }
  params->array_len = array_len;

  GuestfsSession *session = (GuestfsSession *) opaque;

  g_signal_emit(session, signals[params->event], 0, params);

  guestfs_session_event_params_free(params);
}
