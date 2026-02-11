ladish_room_destroy(ladish_room_handle room_handle)
{
  if (!room_ptr->template)
  {

    ASSERT((room_ptr->project_dir == NULL && room_ptr->project_name == NULL) || (room_ptr->project_dir != NULL && room_ptr->project_name != NULL));
    free(room_ptr->project_dir);
    free(room_ptr->project_name);
    free(room_ptr->project_description);
    free(room_ptr->project_notes);

    ASSERT(!room_ptr->started);


    if (ladish_studio_is_started())
    {
      ladish_graph_clear(room_ptr->graph, remove_port_callback);
    }

    cdbus_object_path_destroy(cdbus_g_dbus_connection, room_ptr->dbus_object);
    ladish_app_supervisor_destroy(room_ptr->app_supervisor);

    ladish_graph_remove_client(room_ptr->owner, room_ptr->client);
    ladish_client_destroy(room_ptr->client);

    ladish_studio_room_disappeared((ladish_room_handle)room_ptr);
    ladish_studio_release_room_index(room_ptr->index);

    free(room_ptr->object_path);
  }

  ladish_graph_destroy(room_ptr->graph);
  free(room_ptr->name);
  free(room_ptr);
}
