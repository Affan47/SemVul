_probe_front_button(_HpOption this, HpScsi scsi,
                                      HpOptSet UNUSEDARG optset, HpData data)
{
  int val = 0;

  if ( sanei_hp_scl_inquire(scsi, SCL_FRONT_BUTTON, &val, 0, 0)
        != SANE_STATUS_GOOD )
    return SANE_STATUS_UNSUPPORTED;

  _set_size(this, data, sizeof(SANE_Bool));


  if (!this->data_acsr)
  {
      if ( !(this->data_acsr = sanei_hp_accessor_bool_new(data)) )
          return SANE_STATUS_NO_MEM;
  }

  sanei_hp_accessor_setint(this->data_acsr, data, 0);

  return SANE_STATUS_GOOD;
}
