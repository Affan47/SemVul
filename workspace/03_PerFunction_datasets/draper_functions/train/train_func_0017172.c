_program_data_width (HpOption this, HpScsi scsi, HpOptSet optset, HpData data)
{
  HpScl scl = this->descriptor->scl_command;
  int value = sanei_hp_accessor_getint(this->data_acsr, data);
  SANE_Status status;

  if ( sanei_hp_optset_scanmode (optset, data) == HP_SCANMODE_COLOR )
  {
    value *= 3;
    if (value < 24)
    {
      DBG(3,"program_data_width: map datawith from %d to 24\n", (int)value);
      value = 24;
    }
  }
  status = sanei_hp_scl_set(scsi, scl, value);
  return status;
}
