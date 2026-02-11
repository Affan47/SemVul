eprn_map_rgb_color_for_CMY_or_K(gx_device *device,
  const gx_color_value cv[])
{
  gx_color_value red = cv[0], green = cv[1], blue = cv[2];
  static const gx_color_value half = gx_max_color_value/2;
  gx_color_index value = (CYAN_BIT | MAGENTA_BIT | YELLOW_BIT);
  const eprn_Device *dev = (eprn_Device *)device;

#ifdef EPRN_TRACE
  if_debug3(EPRN_TRACE_CHAR,
    "! eprn_map_rgb_color_for_CMY_or_K() called for RGB = (%hu, %hu, %hu),\n",
    red, green, blue);
#endif

  assert(dev->eprn.colour_model == eprn_DeviceGray && red == green &&
      green == blue && (blue == 0 || blue == gx_max_color_value) ||
    dev->eprn.colour_model == eprn_DeviceCMY ||
    dev->eprn.colour_model == eprn_DeviceCMY_plus_K);


  if (red   > half) value &= ~CYAN_BIT;
  if (green > half) value &= ~MAGENTA_BIT;
  if (blue  > half) value &= ~YELLOW_BIT;


  if (dev->eprn.colour_model != eprn_DeviceCMY &&
      value == (CYAN_BIT | MAGENTA_BIT | YELLOW_BIT))
    value = BLACK_BIT;

#ifdef EPRN_TRACE
  if_debug1(EPRN_TRACE_CHAR, "  returning 0x%lX.\n", (unsigned long)value);
#endif
  return value;
}
