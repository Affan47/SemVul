j2k_read_header(
                opj_j2k_t *p_j2k,
                struct opj_image ** p_image,
                OPJ_INT32 * p_tile_x0,
                OPJ_INT32 * p_tile_y0,
                OPJ_UINT32 * p_tile_width,
                OPJ_UINT32 * p_tile_height,
                OPJ_UINT32 * p_nb_tiles_x,
                OPJ_UINT32 * p_nb_tiles_y,
                struct opj_stream_private *p_stream,
                struct opj_event_mgr * p_manager
              )
{

  assert(p_j2k != 00);
  assert(p_stream != 00);
  assert(p_manager != 00);

  *p_image = 00;

  p_j2k->m_image = opj_image_create0();
  if
    (! p_j2k->m_image)
  {
    return false;
  }


  j2k_setup_decoding_validation (p_j2k);


  if
    (! j2k_exec(p_j2k,p_j2k->m_validation_list,p_stream,p_manager))
  {
    opj_image_destroy(p_j2k->m_image);
    p_j2k->m_image = 00;
    return false;
  }


  j2k_setup_header_reading(p_j2k);


  if
    (! j2k_exec (p_j2k,p_j2k->m_procedure_list,p_stream,p_manager))
  {
    opj_image_destroy(p_j2k->m_image);
    p_j2k->m_image = 00;
    return false;
  }
  *p_image = p_j2k->m_image;
  * p_tile_x0 = p_j2k->m_cp.tx0;
    * p_tile_y0 = p_j2k->m_cp.ty0;
  * p_tile_width = p_j2k->m_cp.tdx;
    * p_tile_height = p_j2k->m_cp.tdy;
  * p_nb_tiles_x = p_j2k->m_cp.tw;
  * p_nb_tiles_y = p_j2k->m_cp.th;
  return true;
}
