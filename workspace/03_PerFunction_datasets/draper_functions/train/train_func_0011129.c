get_cshading_values(Microtek2_Scanner *ms,
                    uint8_t color,
                    uint32_t pixel,
                    float shading_factor,
                    int right_to_left,
                    float *s_d,
                    float *s_w)
{
  Microtek2_Device *md;
  uint32_t csh_offset;

  md = ms->dev;

  if ( right_to_left == 1 )
    csh_offset = (color + 1) * ms->ppl - 1 - pixel;
  else
    csh_offset = color * ms->ppl + pixel;

  if ( ( md->shading_depth > 8 ) && ( ms->lut_entry_size == 2) )

    {
      if ( ms->condensed_shading_d != NULL )
          *s_d = (float) *( (uint16_t *)ms->condensed_shading_d
                                         + csh_offset );
      else
          *s_d = 0.0;

      *s_w = (float) *( (uint16_t *)ms->condensed_shading_w
                                     + csh_offset );
      *s_w /= shading_factor;
      *s_d /= shading_factor;
    }

  else

    {
      *s_w = (float) *( ms->condensed_shading_w + csh_offset );
      if ( ms->condensed_shading_d != NULL )
        *s_d = (float) *( ms->condensed_shading_d + csh_offset );
      else
        *s_d = 0.0;
    }
  return SANE_STATUS_GOOD;
}
