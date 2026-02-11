hp_get_simulation_map (const char *devname, const HpDeviceInfo *info)
{
 hp_bool_t     sim_gamma, sim_brightness, sim_contrast;
 int           k, ind;
 const unsigned char *map = NULL;
 static unsigned char map8x8[256];

  sim_gamma = info->simulate.gamma_simulate;
  sim_brightness = sanei_hp_device_simulate_get (devname, SCL_BRIGHTNESS);
  sim_contrast = sanei_hp_device_simulate_get (devname, SCL_CONTRAST);

  if ( sim_gamma )
  {
    map = &(info->simulate.gamma_map[0]);
  }
  else if ( sim_brightness && sim_contrast )
  {
    for (k = 0; k < 256; k++)
    {
      ind = info->simulate.contrast_map[k];
      map8x8[k] = info->simulate.brightness_map[ind];
    }
    map = &(map8x8[0]);
  }
  else if ( sim_brightness )
    map = &(info->simulate.brightness_map[0]);
  else if ( sim_contrast )
    map = &(info->simulate.contrast_map[0]);

  return map;
}
