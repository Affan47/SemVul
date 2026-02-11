notify_conn(struct conn_list *dest,
                 const struct tile *ptile,
                 enum event_type event,
                 const struct ft_color color,
                 const char *format, ...)
{
  struct packet_chat_msg genmsg;
  va_list args;

  va_start(args, format);
  vpackage_event(&genmsg, ptile, event, color, format, args);
  va_end(args);

  notify_conn_packet(dest, &genmsg);

  if (!dest || dest == game.est_connections) {

    event_cache_add_for_all(&genmsg);
  }
}
