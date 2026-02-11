compute_dark_shading_data (Avision_Scanner* s,
			   struct calibration_format* format, uint8_t* data)
{
  uint16_t map_value = DEFAULT_DARK_SHADING;
  uint16_t rgb_map_value[3];

  int elements_per_line, i;

  DBG (3, "compute_dark_shading_data:\n");

  if (s->hw->inquiry_max_shading_target != INVALID_DARK_SHADING)
    map_value = s->hw->inquiry_max_shading_target << 8;

  rgb_map_value[0] = format->r_dark_shading_target;
  rgb_map_value[1] = format->g_dark_shading_target;
  rgb_map_value[2] = format->b_dark_shading_target;

  for (i = 0; i < format->channels; ++i) {
    if (rgb_map_value[i] == INVALID_DARK_SHADING)
      rgb_map_value[i] = map_value;
  }

  if (format->channels == 1) {

    rgb_map_value[0] = rgb_map_value[1] = rgb_map_value[2] = rgb_map_value[1];
  }

  elements_per_line = format->pixel_per_line * format->channels;


  for (i = 0; i < elements_per_line; ++i)
    {
      uint16_t tmp_data = get_double_le((data + i*2));
      if (tmp_data > rgb_map_value[i % 3]) {
	set_double ((data + i*2), tmp_data - rgb_map_value[i % 3]);
      }
      else {
	set_double ((data + i*2), 0);
      }
    }
}
