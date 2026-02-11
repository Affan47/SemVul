message_options_save(struct section_file *file,
                                 const char *prefix)
{
  enum event_type event;
  int i = 0;

  for (event = event_type_begin(); event != event_type_end();
       event = event_type_next(event)) {
    secfile_insert_str(file, event_type_name(event),
                       "messages.event%d.name", i);
    secfile_insert_int(file, messages_where[i],
                       "messages.event%d.where", i);
    i++;
  }

  secfile_insert_int(file, i, "messages.count");
}
