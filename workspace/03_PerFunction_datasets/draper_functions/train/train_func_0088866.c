jp2_read_header_procedure(
           opj_jp2_t *jp2,
           opj_stream_private_t *cio,
           opj_event_mgr_t * p_manager)
{
  opj_jp2_box_t box;
  unsigned int l_nb_bytes_read;
  const opj_jp2_header_handler_t * l_current_handler;
  unsigned int l_last_data_size = BOX_SIZE;
  unsigned int l_current_data_size;
  unsigned char * l_current_data = 00;


  assert(cio != 00);
  assert(jp2 != 00);
  assert(p_manager != 00);

  l_current_data = (unsigned char*)opj_malloc(l_last_data_size);

  if
    (l_current_data == 00)
  {
    opj_event_msg(p_manager, EVT_ERROR, "Not enough memory to handle jpeg2000 file header\n");
    return false;
  }
  memset(l_current_data, 0 , l_last_data_size);
  while
    (jp2_read_boxhdr(&box,&l_nb_bytes_read,cio,p_manager))
  {

    if
      (box.type == JP2_JP2C)
    {
      if
        (jp2->jp2_state & JP2_STATE_HEADER)
      {
        jp2->jp2_state |= JP2_STATE_CODESTREAM;
        opj_free(l_current_data);
        return true;
      }
      else
      {
        opj_event_msg(p_manager, EVT_ERROR, "bad placed jpeg codestream\n");
        opj_free(l_current_data);
        return false;
      }
    }
    else if
      (box.length == 0)
    {
      opj_event_msg(p_manager, EVT_ERROR, "Cannot handle box of undefined sizes\n");
      opj_free(l_current_data);
      return false;
    }

    l_current_handler = jp2_find_handler(box.type);
    l_current_data_size = box.length - l_nb_bytes_read;

    if
      (l_current_handler != 00)
    {
      if
        (l_current_data_size > l_last_data_size)
      {
        l_current_data = (unsigned char*)opj_realloc(l_current_data,l_current_data_size);
        l_last_data_size = l_current_data_size;
      }
      l_nb_bytes_read = opj_stream_read_data(cio,l_current_data,l_current_data_size,p_manager);
      if
        (l_nb_bytes_read != l_current_data_size)
      {
        opj_event_msg(p_manager, EVT_ERROR, "Problem with reading JPEG2000 box, stream error\n");
        opj_free(l_current_data);
        return false;
      }
      if
        (! l_current_handler->handler(jp2,l_current_data,l_current_data_size,p_manager))
      {
        opj_free(l_current_data);
        return false;
      }
    }
    else
    {
      jp2->jp2_state |= JP2_STATE_UNKNOWN;
      if
        (opj_stream_skip(cio,l_current_data_size,p_manager) != l_current_data_size)
      {
        opj_event_msg(p_manager, EVT_ERROR, "Problem with skipping JPEG2000 box, stream error\n");
        opj_free(l_current_data);
        return false;
      }
    }
  }
  opj_free(l_current_data);
  return true;
}
