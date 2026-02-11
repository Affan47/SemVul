_hb_buffer_add_output_glyphs (hb_buffer_t *buffer,
			      unsigned int num_in,
			      unsigned int num_out,
			      const hb_codepoint_t *glyph_data,
			      unsigned short component,
			      unsigned short lig_id)
{
  unsigned int i;
  unsigned int mask;
  unsigned int cluster;

  if (buffer->out_string != buffer->in_string ||
      buffer->out_pos + num_out > buffer->in_pos + num_in)
  {
    hb_buffer_ensure_separate (buffer, buffer->out_pos + num_out);
  }

  mask = buffer->in_string[buffer->in_pos].mask;
  cluster = buffer->in_string[buffer->in_pos].cluster;
  if (component == 0xFFFF)
    component = buffer->in_string[buffer->in_pos].component;
  if (lig_id == 0xFFFF)
    lig_id = buffer->in_string[buffer->in_pos].lig_id;

  for (i = 0; i < num_out; i++)
  {
    hb_internal_glyph_info_t *info = &buffer->out_string[buffer->out_pos + i];
    info->codepoint = glyph_data[i];
    info->mask = mask;
    info->cluster = cluster;
    info->component = component;
    info->lig_id = lig_id;
    info->gproperty = HB_BUFFER_GLYPH_PROPERTIES_UNKNOWN;
  }

  buffer->in_pos  += num_in;
  buffer->out_pos += num_out;
  buffer->out_length = buffer->out_pos;
}
