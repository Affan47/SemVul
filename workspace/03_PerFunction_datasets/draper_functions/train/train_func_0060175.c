eprn_map_rgb_color_for_CMY_or_K_flex(gx_device *device,
  const gx_color_value cv[])
{
  gx_color_value red = cv[0], green = cv[1], blue = cv[2];
  const eprn_Device *dev = (eprn_Device *)device;

#ifdef EPRN_TRACE
  if_debug3(EPRN_TRACE_CHAR,
    "! eprn_map_rgb_color_for_CMY_or_K_flex() called for "
      "RGB = (%hu, %hu, %hu).\n",
    red, green, blue);
#endif


  gx_color_value tmpcv[4];
  if (dev->eprn.colour_model != eprn_DeviceCMY && red == green && green == blue) {
    tmpcv[0] = 0; tmpcv[1] = 0; tmpcv[2] = 0;
    tmpcv[3] = gx_max_color_value - red;
    return eprn_map_cmyk_color_flex(device, tmpcv);

  }
  tmpcv[0] = gx_max_color_value - red;
  tmpcv[1] = gx_max_color_value - green;
  tmpcv[2] = gx_max_color_value - blue;
  tmpcv[3] = 0;
  return eprn_map_cmyk_color_flex(device, tmpcv);
}
