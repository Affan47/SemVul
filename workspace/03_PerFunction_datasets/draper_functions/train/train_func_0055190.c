jp2_decode(opj_jp2_t *jp2, struct opj_stream_private *cio, struct opj_event_mgr * p_manager)
{

  struct opj_image * image = j2k_decode(jp2->j2k, cio, p_manager);
  if
    (!image)
  {
    opj_event_msg(p_manager, EVT_ERROR, "Failed to decode J2K image\n");
    return false;
  }


  if (jp2->enumcs == 16)
    image->color_space = CLRSPC_SRGB;
  else if (jp2->enumcs == 17)
    image->color_space = CLRSPC_GRAY;
  else if (jp2->enumcs == 18)
    image->color_space = CLRSPC_SYCC;
  else
    image->color_space = CLRSPC_UNKNOWN;
  return image;
}
