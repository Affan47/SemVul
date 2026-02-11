_enable_out8 (HpOption UNUSEDARG this, HpOptSet optset, HpData data,
              const HpDeviceInfo *info)
{
  if (hp_optset_isEnabled (optset, data, SANE_NAME_BIT_DEPTH, info))
  {
    int data_width = sanei_hp_optset_data_width (optset, data);
    return (((data_width > 8) && (data_width <= 16)) || (data_width > 24));
  }
  return 0;
}
