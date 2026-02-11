hp_option_updateEnable (HpOption this, HpOptSet optset, HpData data,
                        const HpDeviceInfo *info)
{
  hp_bool_t 	(*f)(HpOption, HpOptSet, HpData, const HpDeviceInfo *)
                    = this->descriptor->enable;
  _HpSaneOption	optd 	= _hp_option_saneoption(this, data);

  if (!f || (*f)(this, optset, data, info))
      optd->cap &= ~SANE_CAP_INACTIVE;
  else
      optd->cap |= SANE_CAP_INACTIVE;
}
