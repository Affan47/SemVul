j2k_write_siz(
              opj_j2k_t *p_j2k,
              struct opj_stream_private *p_stream,
              struct opj_event_mgr * p_manager
          )
{
  OPJ_UINT32 i;
  OPJ_UINT32 l_size_len;
  OPJ_BYTE * l_current_ptr;
  opj_image_t * l_image = 00;
  opj_cp_t *cp = 00;
  opj_image_comp_t * l_img_comp = 00;


  assert(p_stream != 00);
  assert(p_j2k != 00);
  assert(p_manager != 00);

  l_image = p_j2k->m_image;
  cp = &(p_j2k->m_cp);
  l_size_len = 40 + 3 * l_image->numcomps;
  l_img_comp = l_image->comps;

  if
    (l_size_len > p_j2k->m_specific_param.m_encoder.m_header_tile_data_size)
  {
    p_j2k->m_specific_param.m_encoder.m_header_tile_data
      = (OPJ_BYTE*)opj_realloc(
        p_j2k->m_specific_param.m_encoder.m_header_tile_data,
        l_size_len);
    if
      (! p_j2k->m_specific_param.m_encoder.m_header_tile_data)
    {
      return false;
    }
    p_j2k->m_specific_param.m_encoder.m_header_tile_data_size = l_size_len;
  }

  l_current_ptr = p_j2k->m_specific_param.m_encoder.m_header_tile_data;


  opj_write_bytes(l_current_ptr,J2K_MS_SIZ,2);
  l_current_ptr+=2;
  opj_write_bytes(l_current_ptr,l_size_len-2,2);
  l_current_ptr+=2;
  opj_write_bytes(l_current_ptr, cp->rsiz, 2);
  l_current_ptr+=2;
  opj_write_bytes(l_current_ptr, l_image->x1, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, l_image->y1, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, l_image->x0, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, l_image->y0, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, cp->tdx, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, cp->tdy, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, cp->tx0, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, cp->ty0, 4);
  l_current_ptr+=4;
  opj_write_bytes(l_current_ptr, l_image->numcomps, 2);
  l_current_ptr+=2;
  for
    (i = 0; i < l_image->numcomps; ++i)
  {

    opj_write_bytes(l_current_ptr, l_img_comp->prec - 1 + (l_img_comp->sgnd << 7), 1);
    ++l_current_ptr;
    opj_write_bytes(l_current_ptr, l_img_comp->dx, 1);
    ++l_current_ptr;
    opj_write_bytes(l_current_ptr, l_img_comp->dy, 1);
    ++l_current_ptr;
    ++l_img_comp;
  }
  if
    (opj_stream_write_data(p_stream,p_j2k->m_specific_param.m_encoder.m_header_tile_data,l_size_len,p_manager) != (OPJ_INT32)l_size_len)
  {
    return false;
  }
  return true;
}
