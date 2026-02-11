free_media(bgav_sdp_media_desc_t * m)
  {
  int i;
  MY_FREE(m->media);
  MY_FREE(m->protocol);

  for(i = 0; i < m->num_formats; i++)
    MY_FREE(m->formats[i]);
  MY_FREE(m->formats);


  MY_FREE(m->media_title);
  free_connection_desc(&m->connection);
  free_bandwidth_desc(&m->bandwidth);
  free_key_desc(&m->key);
  free_attributes(&m->attributes);
  }
