jcr_main_new_stream(void) {

  jcr->current = NULL;
  if (jcr->parser)
    XML_ParserFree(jcr->parser);
  jcr->fd = -1;

  jcr->stream_state = _STREAM_INIT_STATE;
  jcr->parser = XML_ParserCreate(NULL);
  XML_SetElementHandler(jcr->parser, (void *)jcr_start_element, (void *)jcr_end_element);
  XML_SetCharacterDataHandler(jcr->parser, (void *)jcr_cdata);
  XML_SetUserData(jcr->parser, NULL);

  while (jcr_socket_connect()) {
    sleep(2);
  }

  jcr->gio = g_io_channel_unix_new(jcr->fd);
  g_io_channel_set_encoding(jcr->gio, NULL, NULL);
  g_io_channel_set_buffered(jcr->gio, FALSE);

  jcr->dthread = g_thread_create((void *)jcr_queue_deliver, NULL, TRUE, NULL);

  jcr->gmain_watch_source = g_io_add_watch_full(jcr->gio, G_PRIORITY_HIGH, (G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_NVAL), (void *)jcr_read_data, NULL, NULL);
  jcr_send_start_stream();
  log_notice(JDBG, "Server stream connected.");
}
