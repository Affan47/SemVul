j2k_write_coc(
              opj_j2k_t *p_j2k,
              OPJ_UINT32 p_comp_no,
              struct opj_stream_private *p_stream,
              struct opj_event_mgr * p_manager
            )
{
  OPJ_UINT32 l_coc_size,l_remaining_size;
  OPJ_UINT32 l_comp_room;


  assert(p_j2k != 00);
  assert(p_manager != 00);
  assert(p_stream != 00);

  l_comp_room = (p_j2k->m_image->numcomps <= 256) ? 1 : 2;

  l_coc_size = 5 + l_comp_room + j2k_get_SPCod_SPCoc_size(p_j2k,p_j2k->m_current_tile_number,p_comp_no);
  if
    (l_coc_size > p_j2k->m_specific_param.m_encoder.m_header_tile_data_size)
  {
    p_j2k->m_specific_param.m_encoder.m_header_tile_data
      = (OPJ_BYTE*)opj_realloc(
        p_j2k->m_specific_param.m_encoder.m_header_tile_data,
        l_coc_size);
    if
      (! p_j2k->m_specific_param.m_encoder.m_header_tile_data)
    {
      return false;
    }
    p_j2k->m_specific_param.m_encoder.m_header_tile_data_size = l_coc_size;
  }

  j2k_write_coc_in_memory(p_j2k,p_comp_no,p_j2k->m_specific_param.m_encoder.m_header_tile_data,&l_remaining_size,p_manager);

  if
    (opj_stream_write_data(p_stream,p_j2k->m_specific_param.m_encoder.m_header_tile_data,l_coc_size,p_manager) != l_coc_size)
  {
    return false;
  }
  return true;
}
