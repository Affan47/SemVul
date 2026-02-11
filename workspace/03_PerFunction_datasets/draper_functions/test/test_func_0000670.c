create_room_template(
  const uuid_t uuid_ptr,
  const char * name,
  struct room_descriptor * room_descriptor_ptr)
{
  ladish_room_handle room;
  ladish_graph_handle graph;
  ladish_client_handle capture;
  ladish_client_handle playback;

  if (!create_empty_room_template(uuid_ptr, name, &room))
  {
    log_error("ladish_room_create() failed for room template \"%s\".", name);
    goto fail;
  }

  graph = ladish_room_get_graph(room);

  if (!ladish_client_create(ladish_wkclient_capture, &capture))
  {
    log_error("ladish_client_create() failed to create capture client to room template \"%s\".", name);
    goto fail_destroy;
  }

  if (!ladish_graph_add_client(graph, capture, "Capture", false))
  {
    log_error("ladish_graph_add_client() failed to add capture client to room template \"%s\".", name);
    goto fail_destroy;
  }

  if (!ladish_client_create(ladish_wkclient_playback, &playback))
  {
    log_error("ladish_client_create() failed to create playback client to room template \"%s\".", name);
    goto fail_destroy;
  }

  if (!ladish_graph_add_client(graph, playback, "Playback", false))
  {
    log_error("ladish_graph_add_client() failed to add playback client to room template \"%s\".", name);
    goto fail_destroy;
  }

  room_descriptor_ptr->name = ladish_room_get_name(room);
  room_descriptor_ptr->room = room;
  room_descriptor_ptr->graph = graph;
  room_descriptor_ptr->capture = capture;
  room_descriptor_ptr->playback = playback;

  return true;

fail_destroy:
  ladish_room_destroy(room);
fail:
  return false;
}
