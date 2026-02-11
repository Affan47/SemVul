_program_scanmode (HpOption this, HpScsi scsi, HpOptSet optset, HpData data)
{
  enum hp_scanmode_e	new_mode  = hp_option_getint(this, data);
  int	invert	 = 0;
  int   fw_invert = 0;
  int   is_model_4c = 0;
  enum hp_device_compat_e compat;
  hp_bool_t  disable_xpa = ( sanei_hp_optset_scan_type (optset, data)
                               != SCL_XPA_SCAN );


  if (   (sanei_hp_device_probe (&compat,scsi) == SANE_STATUS_GOOD)
      && (compat & HP_COMPAT_4C) )
  {
    is_model_4c = 1;
    DBG(3, "program_scanmode: model 3c/4c/6100C recognized\n");
  }

  if (is_model_4c)
  {
    const HpDeviceInfo *info;
    int data_width;
    HpOption option;
    int is_preview = 0;


    option = hp_optset_getByName (optset, SANE_NAME_PREVIEW);
    if ( option )
      is_preview = hp_option_getint (option, data);

    info = sanei_hp_device_info_get ( sanei_hp_scsi_devicename  (scsi) );

    if (   (!is_preview)
        && hp_optset_isEnabled (optset, data, SANE_NAME_BIT_DEPTH, info))
    {
      data_width = sanei_hp_optset_data_width (optset, data);
      if ((data_width == 10) || (data_width == 30))
      {
        fw_invert = 1;
        DBG(3, "program_scanmode: firmware is doing inversion\n");
      }
    }
  }


  DBG(3, "program_scanmode: disable XPA = %d\n", (int)disable_xpa);
  sanei_hp_scl_set(scsi, SCL_XPA_DISABLE, disable_xpa);

  RETURN_IF_FAIL( hp_option_download(this, data, optset, scsi) );

  switch (new_mode) {
  case HP_SCANMODE_GRAYSCALE:

      RETURN_IF_FAIL( sanei_hp_scl_set(scsi, SCL_DATA_WIDTH, 8) );
      invert = 1;
      if (fw_invert) invert = 0;

      if ( (!disable_xpa) && sanei_hp_is_active_xpa (scsi) ) invert = 0;
      break;
  case HP_SCANMODE_COLOR:
      invert = 1;
      if (fw_invert) invert = 0;

      if ( (!disable_xpa) && sanei_hp_is_active_xpa (scsi) ) invert = 0;
      break;
  default:
      break;
  }

  return sanei_hp_scl_set(scsi, SCL_INVERSE_IMAGE, invert);
}
