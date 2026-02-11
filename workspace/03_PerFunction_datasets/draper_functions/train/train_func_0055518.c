eprn_map_cmyk_color_flex(gx_device *device,
  const gx_color_value cv[])
{
  gx_color_value cyan = cv[0], magenta = cv[1], yellow = cv[2], black = cv[3];
  gx_color_index value = 0;
  gx_color_value step;
  unsigned int level;
  const eprn_Eprn *eprn = &((eprn_Device *)device)->eprn;

#ifdef EPRN_TRACE
  if_debug4(EPRN_TRACE_CHAR,
    "! eprn_map_cmyk_color_flex() called for CMYK = (%hu, %hu, %hu, %hu),\n",
      cyan, magenta, yellow, black);
#endif


  if (eprn->colour_model != eprn_DeviceGray) {
    step = gx_max_color_value/eprn->non_black_levels;

    level = yellow/step;
    if (level >= eprn->non_black_levels) level = eprn->non_black_levels - 1;
    value = level << eprn->bits_per_colorant;
    level = magenta/step;
    if (level >= eprn->non_black_levels) level = eprn->non_black_levels - 1;
    value = (value | level) << eprn->bits_per_colorant;
    level = cyan/step;
    if (level >= eprn->non_black_levels) level = eprn->non_black_levels - 1;
    value = (value | level) << eprn->bits_per_colorant;
  }
  if (eprn->colour_model != eprn_DeviceCMY) {
    step = gx_max_color_value/eprn->black_levels;
    level = black/step;
    if (level >= eprn->black_levels) level = eprn->black_levels - 1;
    value |= level;
  }

#ifdef EPRN_TRACE
  if_debug1(EPRN_TRACE_CHAR, "  returning 0x%lX.\n", (unsigned long)value);
#endif
  return value;
}
