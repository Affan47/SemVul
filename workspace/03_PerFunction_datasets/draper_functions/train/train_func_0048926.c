bgav_sdp_free(bgav_sdp_t * s)
  {
  int i;
  free_origin(&s->origin);

  MY_FREE(s->session_name);
  MY_FREE(s->session_description);
  MY_FREE(s->uri);
  MY_FREE(s->email);
  MY_FREE(s->phone);

  free_connection_desc(&s->connection);
  free_bandwidth_desc(&s->bandwidth);
  free_key_desc(&s->key);
  free_attributes(&s->attributes);

  for(i = 0; i < s->num_media; i++)
    free_media(&s->media[i]);
  MY_FREE(s->media);
  }
